import Data.Char
import Data.List
import Date_stuff

--EventInfo type was given by the course, as well as main and loop functions

data EventInfo = EventInfo { name :: String
                           , place :: String
                           , date :: Date
                           } deriving(Eq)

makeEvent :: String -> String -> Date -> EventInfo
makeEvent nimi paikka aika = EventInfo {name = nimi, place = paikka, date = aika}



main = loop $ return []
 
loop :: IO [EventInfo] -> IO ()
loop ioEvents = do
 putStrLn "Hello! Give me an input"
 input <- getLine
 if input == "Quit"
   then putStrLn "bye"
   else doCommand input ioEvents


doCommand :: String -> IO [EventInfo] -> IO ()
doCommand input ioEvents = do
  events <- ioEvents
  let komento = words input
  case komento of
    ("Quit" : _) -> putStrLn "bye"
    ("Event" : _ : _ : "happens" : "at" : _ : _ : "on" : _) -> do
        let maybeEvent = addEvent input
        case maybeEvent of
          Just event -> do
            let updatedEvents = event : filter (\e -> name e /= name event) events
            putStrLn "ok"
            loop (return updatedEvents)
          Nothing -> do
            putStrLn "Bad date"
            loop (return events)
    ("Tell" : "me" : "about" : _) -> do
        let eventStr = takeWhile (/= '\'')(drop 1 (dropWhile (/= '\'') input))
        tellAboutEvent eventStr events
        loop (return events)
    ("What" : "happens" : "on" : _) -> do
        let dateStr = takeWhile (/= '\'')(drop 1 (dropWhile (/= '\'') input))
        tellAboutDate dateStr events
        loop (return events)
    ("What" : "happens" : "at" : _) -> do
        let placeStr = takeWhile (/= '\'')(drop 1 (dropWhile (/= '\'') input))
        tellAboutPlace placeStr events
        loop (return events)
    _ -> do 
        printError
        loop (return events)

addEvent :: String -> Maybe EventInfo
addEvent komento = do
    let sanat = words komento
        nimi = removeDot $ unwords $ take 2 (tail sanat)
        paikka = removeDot $ unwords $ take 2 (drop 5 sanat)
        aikaStr = removeDot $ head (drop 8 sanat)
        y = readMaybe $ take 4 aikaStr :: Maybe Integer
        m = readMaybe $ take 2 (drop 5 aikaStr) :: Maybe Integer
        d = readMaybe $ take 2 (drop 8 aikaStr) :: Maybe Integer
    case (y, m, d) of
        (Just y, Just m, Just d) -> do
            let maybeDate = makeMaybeDate y m d
            case maybeDate of
                Nothing -> Nothing
                Just date -> Just $ makeEvent nimi paikka date
        _ -> Nothing

tellAboutEvent :: String -> [EventInfo] -> IO ()
tellAboutEvent _ [] = do putStrLn "I do not know of such event"
tellAboutEvent str (x:xs)
    | name x == str = do
        putStrLn $ "Event " ++ str ++ " happens at " ++ place x ++ " on " ++ dateToString (date x)
    | otherwise = tellAboutEvent str xs

tellAboutDate :: String -> [EventInfo] -> IO ()
tellAboutDate str events = do 
    let eventList = [x | x <- events, dateToString(date x)==str]
    let sortedEvents = sortByName eventList 
    case eventList of
        [] -> putStrLn "Nothing that I know of"
        _ -> printDateEvents sortedEvents


tellAboutPlace :: String -> [EventInfo] -> IO ()
tellAboutPlace str events = do
    let eventList = [x | x <- events, (place x)==str]
    let sortedEvents = sortByName eventList 
    case eventList of
        [] -> putStrLn "Nothing that I know of"
        _ -> printEvents sortedEvents


sortByName :: [EventInfo] -> [EventInfo]
sortByName = sortBy (\event1 event2 -> compare (name event1) (name event2))

printDateEvents :: [EventInfo] -> IO ()
printDateEvents [] = putStr ""
printDateEvents (x:xs) = do
    putStrLn $ "Event " ++ name x ++ " happens on " ++ dateToString (date x) 
    printDateEvents xs


printEvents :: [EventInfo] -> IO ()
printEvents [] = putStr ""
printEvents (x:xs) = do
    putStrLn $ "Event " ++ name x ++ " happens at " ++ place x 
    printEvents xs


dateToString :: Date -> String
dateToString (Date year month day) =
  let y = fromYear year
      m = fromMonth month
      d = fromDay day
      addZero x = if x < 10 then "0" ++ show x else show x
  in show y ++ "-" ++ addZero m ++ "-" ++ addZero d

maybeEventToList :: Maybe EventInfo -> IO [EventInfo]
maybeEventToList Nothing = return []
maybeEventToList (Just event) = return [event]

printError :: IO ()
printError = do
    putStrLn "I do not understand that. I understand the following:"
    putStrLn "*Event <name> happens at <place> on <date>"
    putStrLn "*Tell me about <eventname>"
    putStrLn "*What happens on <date>"
    putStrLn "*What happens at <place>"
    putStrLn "*Quit"


readMaybe :: (Read a) => String -> Maybe a
readMaybe st = case reads st of [(x,"")] -> Just x
                                _ -> Nothing

removeDot :: String -> String
removeDot str = filter (\c -> c /= '\'') str
