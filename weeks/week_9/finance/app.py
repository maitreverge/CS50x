# TO DO : sell

import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# DONE
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Recuperer les infos de stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )

    # Recuperer le cash de l'utulisateur
    cash = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]
    # Iterer sur le stock et faire les maths necessaires
    grand_total = cash
    total_value = cash

    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["total_shares"] * stock["price"]
        total_value = total_value + stock["value"]
        grand_total = grand_total + stock["value"]

    return render_template(
        "index.html",
        stocks=stocks,
        cash=cash,
        grand_total=grand_total,
        total_value=total_value,
    )


# DONE
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide a positive integer number of shares")

        quote = lookup(symbol)
        if quote is None:
            return apology("Not found symbol")

        price = quote["price"]
        total_cost = int(shares) * price

        cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]

        if cash < total_cost:
            return apology("Cash is insufisant")

        # Update de la table
        db.execute(
            "UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
            total_cost=total_cost,
            user_id=session["user_id"],
        )

        # Ajout de l'achat a l'historique de la table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
            user_id=session["user_id"],
            symbol=symbol,
            shares=shares,
            price=price,
        )

        flash(f"You just buy {shares} shares of {symbol} for {usd(total_cost)}!")
        return redirect("/")
    else:
        return render_template("buy.html")


# TO DO
@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC",
        user_id=session["user_id"],
    )
    return render_template("history.html", transactions=transactions)


# DONE
@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


# DONE
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


# DONE
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Symbole invalide, veuillez réessayer", 400)
        return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


def valid_password(password):
    # chekcs if the password has at least one letter
    letters = re.search(r"[a-zA-Z]", password)

    # checks if the password got at least one digit
    digit = re.search(r"\d", password)

    # checks if the password got at least one symbol
    symbol = re.search(r"[!@£$%^&*()_+{}~`?><,§±]", password)

    if letters and digit and symbol:
        return True
    else:
        return False


# DONE
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Check if passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # BONUS : Chekcs is the password got all the requirements
        if not valid_password(request.form.get("password")):
            return apology(
                "Password must contain at least one letter, one digit and one special caracter",
                400,
            )

        # Query database for existing username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Check if the username already exists
        if len(rows) != 0:
            return apology("username already exists", 400)

        # Insert the new user into the database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            request.form.get("username"),
            generate_password_hash(request.form.get("password")),
        )

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Remebering whic one is connected
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


# DONE
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("Please provide symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Please provide a positive int")
        else:
            shares = int(shares)

        # boucler la boucle

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("not enough shares")
                else:
                    quote = lookup(symbol)
                    if quote is None:
                        return apology(" Symbol not found")
                    price = quote["price"]
                    total_sale = shares * price

                    # execution de la data base en for loops. Update de la table users
                    db.execute(
                        "UPDATE users set CASH = cash + :total_sale WHERE id = :user_id ",
                        total_sale=total_sale,
                        user_id=session["user_id"],
                    )

                    # ajout de la table dans l'historique
                    db.execute(
                        "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                        user_id=session["user_id"],
                        symbol=symbol,
                        shares=shares,
                        price=price,
                    )

                    flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}!")
                    return redirect("/")

        return apology("symbol not found")
    else:
        return render_template("sell.html", stocks=stocks)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """User investment"""

    if request.method == "POST":
        id = session["user_id"]
        user_cash = request.form.get("cash")
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=id)

        total_amount = cash[0]["cash"] + int(user_cash)
        db.execute(
            "UPDATE users SET cash = :total_amount WHERE id = :id",
            total_amount=total_amount,
            id=id,
        )

        flash("Transaction successfully!")
        return redirect("/")

    else:
        return render_template("deposit.html")
