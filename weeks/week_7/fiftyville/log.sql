-- Keep a log of any SQL queries you execute as you solve the mystery.

-- FIRST LOG :
SELECT id, street, description FROM crime_scene_reports WHERE YEAR = 2021 AND month = 07 AND day = 28;
-- gave me those results : | 295 | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

-- SECOND LOG --
SELECT id, activity, license_plate, minute
   ...> FROM bakery_security_logs
   ...> WHERE YEAR = 2021 AND month = 07 AND day = 28 AND hour = 10;
-- This log gave me :
+-----+----------+---------------+--------+
| id  | activity | license_plate | minute |
+-----+----------+---------------+--------+
| 258 | entrance | R3G7486       | 8      |
| 259 | entrance | 13FNH73       | 14     |
| 260 | exit     | 5P2BI95       | 16     |
| 261 | exit     | 94KL13X       | 18     |
| 262 | exit     | 6P58WS2       | 18     |
| 263 | exit     | 4328GD8       | 19     |
| 264 | exit     | G412CB7       | 20     |
| 265 | exit     | L93JTIZ       | 21     |
| 266 | exit     | 322W7JE       | 23     |
| 267 | exit     | 0NTHK55       | 23     |
| 268 | exit     | 1106N58       | 35     |
| 269 | entrance | NRYN856       | 42     |
| 270 | entrance | WD5M8I6       | 44     |
| 271 | entrance | V47T75I       | 55     |
+-----+----------+---------------+--------+
-- Not much to consider except a couple of license_plate.
-- now moving on to the interviews.

-- 3rd LOG

SELECT id, name, transcript
FROM interviews
WHERE YEAR = 2021 AND month = 07 AND day = 28;

-- This is the results :
--LEAD 1 | 161 | Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- LEAD 2 | 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- LEAD 3 | 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- LEAD 1 : Look into the bakery system, what we did. Looking up the exiting license plate within 10 minutes of the robery time.

SELECT license_plate
FROM bakery_security_logs
WHERE activity = 'exit' AND YEAR = 2021 AND month = 07 AND day = 28 AND hour = 10 AND minute <= 25;

+---------------+
| license_plate |
+---------------+
| 5P2BI95       |
| 94KL13X       |
| 6P58WS2       |
| 4328GD8       |
| G412CB7       |
| L93JTIZ       |
| 322W7JE       |
| 0NTHK55       |
+---------------+

-- Then I filter those results to get a first lists of name :

SELECT DISTINCT p.name, b.license_plate
FROM bakery_security_logs b
JOIN people p ON b.license_plate = p.license_plate
WHERE b.activity = 'exit' AND b.year = 2021 AND b.month = 7 AND b.day = 28 AND b.hour = 10 AND b.minute <= 25;

-- and we get :

+---------+---------------+
|  name   | license_plate |
+---------+---------------+
| Vanessa | 5P2BI95       |
| Bruce   | 94KL13X       |
| Barry   | 6P58WS2       |
| Luca    | 4328GD8       |
| Sofia   | G412CB7       |
| Iman    | L93JTIZ       |
| Diana   | 322W7JE       |
| Kelsey  | 0NTHK55       |
+---------+---------------+

-- SECOND LEAD : I filtered results of the ATM lead, which give me :

SELECT account_number FROM atm_transactions WHERE YEAR = 2021 AND month = 07 AND day = 28 AND transaction_type
= 'withdraw' AND atm_location = 'Leggett Street';

And this result :

+----------------+
| account_number |
+----------------+
| 28500762       |
| 28296815       |
| 76054385       |
| 49610011       |
| 16153065       |
| 25506511       |
| 81061156       |
| 26013199       |
+----------------+

-- I matched it with the bank account number and ID, to gave me a second name list :

SELECT a.account_number, p.name FROM atm_transactions a
JOIN bank_accounts b ON a.account_number = b.account_number
JOIN people p ON b.person_id = p.id
WHERE a.year = 2021 AND a.month = 7 AND a.day = 28 AND a.transaction_type = 'withdraw' AND a.atm_location = 'Leggett Street';

-- which gave me :

+----------------+---------+
| account_number |  name   |
+----------------+---------+
| 49610011       | Bruce   |
| 26013199       | Diana   |
| 16153065       | Brooke  |
| 28296815       | Kenny   |
| 25506511       | Iman    |
| 28500762       | Luca    |
| 76054385       | Taylor  |
| 81061156       | Benista |
+----------------+---------+

-- LEAD 3 : I filter to get the phone calls on that day

SELECT caller, receiver
FROM phone_calls
WHERE year = 2021 AND month = 07 AND day = 28 AND duration <= 60;

-- and I get

+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (609) 555-5876 | (389) 555-5198 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+

-- Now, based on this caller ID, i need the name

SELECT p.phone_number, p.name
FROM phone_calls pc
JOIN people p ON pc.caller = p.phone_number
WHERE pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND pc.duration <= 60;

-- which gave me

+----------------+---------+
|  phone_number  |  name   |
+----------------+---------+
| (130) 555-0289 | Sofia   |
| (499) 555-9472 | Kelsey  |
| (367) 555-5533 | Bruce   |
| (609) 555-5876 | Kathryn |
| (499) 555-9472 | Kelsey  |
| (286) 555-6063 | Taylor  |
| (770) 555-1861 | Diana   |
| (031) 555-6622 | Carina  |
| (826) 555-1652 | Kenny   |
| (338) 555-6650 | Benista |
+----------------+---------+

-----------------------

-- now comparing with the bank results and licence plates :

+----------------+---------+
|  phone_number  |  name   |
+----------------+---------+
| (367) 555-5533 | Bruce   |
| (770) 555-1861 | Diana   |
+----------------+---------+



+----------------+---------+
| account_number |  name   |
+----------------+---------+
| 49610011       | Bruce   |
| 26013199       | Diana   |
+----------------+---------+

+---------+---------------+
|  name   | license_plate |
+---------+---------------+
| Bruce   | 94KL13X       |
| Diana   | 322W7JE       |
+---------+---------------+

-- after deleting row, I only got 2 matching names on each LEAD.


+----------------+---------+----------------+---------------+
| phone_number   | name    | account_number | license_plate |
+----------------+---------+----------------+---------------+
| (367) 555-5533 | Bruce   | 49610011       | 94KL13X       |
| (770) 555-1861 | Diana   | 26013199       | 322W7JE       |
+----------------+---------+----------------+---------------+

-- Now that we have 2 suspect, we need passport numbers of those two people

SELECT name, passport_number
FROM people
WHERE name = 'Bruce' OR name = 'Diana';

------

+-------+-----------------+
| name  | passport_number |
+-------+-----------------+
| Diana | 3592750733      |
| Bruce | 5773159633      |
+-------+-----------------+

-- We then, based on LEAD 3, that he/she supposed to take the first flight of 29/07/2018, we search for it.

SELECT *
FROM flights
WHERE year = 2021 AND month = 7 AND day = 29
ORDER BY hour LIMIT 1;

and we got
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

-- We then run passport number with flight id

SELECT *
FROM passengers
WHERE flight_id = 36
AND passport_number = 3592750733 OR passport_number = 5773159633;

-- we got :

+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 5773159633      | 4A   |
+-----------+-----------------+------+

-- Bruce is the thief.

-- We need to know where his flight is going.

SELECT airports.city AS destination
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;

+---------------+
|  destination  |
+---------------+
| New York City |
+---------------+

-- Bruce is going to nyc

-- His complice is who he called


-- From lead 2

+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |   | (367) 555-5533 | Bruce   |
| (609) 555-5876 | (389) 555-5198 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+

Bruce called the (375) 555-8161 number, which is :

SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';

+-------+
| name  |
+-------+
| Robin |
+-------+

-- Bruce and Robin, you are BUSTED. Straight to jail. Yeah baby, 1st round is on me.
