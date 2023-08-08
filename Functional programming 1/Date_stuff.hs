module Date_stuff
( Month(..)
, toMonth
, fromMonth
, Day(..)
, toDay
, fromDay
, Year(..)
, toYear
, fromYear
, leapYear
, makeMaybeDate
, Date(..)
) where


data Month = MakeMonth Integer deriving (Eq, Show, Ord)

toMonth :: Integer -> Month
toMonth x = MakeMonth x

fromMonth :: Month -> Integer
fromMonth (MakeMonth i) = i -- Pattern match i out

instance Num Month where
 fromInteger = toMonth
 x + y = let r = fromMonth x + fromMonth y in
    if r < 1 || r > 12 then error "Unnatural addition for month"
    else toMonth r
 x - y = let r = fromMonth x - fromMonth y in
    if r < 1 || r > 12 then error "Unnatural subtraction for month"
    else toMonth r
 x * y = let r = fromMonth x * fromMonth y in
    if r < 1 || r > 12 then error "Unnatural multiplication for month"
    else toMonth r

data Day = MakeDay Integer deriving (Eq, Show, Ord)

toDay :: Integer -> Day
toDay x = MakeDay x

fromDay :: Day -> Integer
fromDay (MakeDay i) = i

instance Num Day where
 fromInteger = toDay
 x + y = toDay $ fromDay x + fromDay y
 x - y = toDay $ fromDay x - fromDay y
 x * y = toDay $ fromDay x * fromDay y

data Year = MakeYear Integer deriving (Eq, Show, Ord)

toYear :: Integer -> Year
toYear x = MakeYear x

fromYear :: Year -> Integer
fromYear (MakeYear i) = i

instance Num Year where
 fromInteger = toYear
 x + y = toYear $ fromYear x + fromYear y
 x - y = toYear $ fromYear x - fromYear y
 x * y = toYear $ fromYear x * fromYear y


data Date = Date { year :: Year, month :: Month, day :: Day } deriving (Eq, Show, Ord)

leapYear (MakeYear y)
 | mod y 400 == 0 = True
 | mod y 100 == 0 = False
 | mod y 4 == 0 = True
 | otherwise = False


makeMaybeDate :: Integer -> Integer -> Integer -> Maybe Date
makeMaybeDate y m d
 | y == 0 = Nothing
 | elem m [1,3,5,7,8,10,12] &&
   elem d [1..31] = makeJustDate y m d
 | elem m [4,6,9,11] &&
   (elem d [1..30]) = makeJustDate y m d
 | m==2 && elem d [1..28] = makeJustDate y m d
 | leapYear (toYear y) && m==2 && d==29 = makeJustDate y m d
 | otherwise = Nothing
 where makeJustDate y m d = Just Date {year = toYear y, month = toMonth m, day = toDay d}

