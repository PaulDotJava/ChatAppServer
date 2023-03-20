-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Erstellungszeit: 20. Mrz 2023 um 01:11
-- Server-Version: 10.4.24-MariaDB
-- PHP-Version: 8.1.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Datenbank: `chatapp`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `directchat`
--

CREATE TABLE `directchat` (
  `cid` int(11) NOT NULL,
  `user1` int(11) NOT NULL,
  `user2` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `directchat`
--

INSERT INTO `directchat` (`cid`, `user1`, `user2`) VALUES
(4, 8, 7),
(6, 11, 7),
(7, 11, 8),
(8, 10, 7),
(9, 14, 7),
(10, 13, 7),
(11, 12, 7),
(12, 7, 15),
(13, 7, 16),
(14, 7, 17),
(15, 7, 18),
(16, 7, 19),
(17, 7, 20),
(18, 21, 7),
(19, 7, 22);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `directmessage`
--

CREATE TABLE `directmessage` (
  `cid` int(11) NOT NULL,
  `mid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `directmessage`
--

INSERT INTO `directmessage` (`cid`, `mid`) VALUES
(4, 66),
(4, 67),
(4, 68),
(4, 69),
(4, 70),
(4, 71),
(4, 72),
(4, 73),
(4, 74),
(4, 75),
(4, 76),
(4, 77),
(4, 78),
(4, 79),
(4, 80),
(4, 81),
(4, 114),
(4, 115),
(4, 116),
(4, 117),
(4, 118),
(4, 119),
(4, 120),
(4, 121),
(4, 122),
(4, 123),
(4, 124),
(6, 106),
(7, 82),
(7, 83),
(7, 84),
(7, 85),
(7, 86),
(7, 87),
(7, 88),
(7, 89),
(7, 90),
(7, 91),
(7, 92),
(7, 93),
(7, 94),
(7, 95),
(7, 96),
(7, 97),
(7, 98),
(7, 99),
(7, 100),
(7, 101),
(7, 102),
(7, 103),
(7, 104),
(8, 105),
(12, 107),
(12, 108),
(12, 109),
(12, 110),
(13, 111),
(13, 112),
(19, 113);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `groupchat`
--

CREATE TABLE `groupchat` (
  `gcid` int(11) NOT NULL,
  `name` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `groupmessage`
--

CREATE TABLE `groupmessage` (
  `gcid` int(11) NOT NULL,
  `mid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `message`
--

CREATE TABLE `message` (
  `mid` int(11) NOT NULL,
  `sender` int(11) NOT NULL,
  `time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `content` text NOT NULL,
  `chunk` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `message`
--

INSERT INTO `message` (`mid`, `sender`, `time`, `content`, `chunk`) VALUES
(66, 7, '2023-02-18 20:30:13', 'lol', 0),
(67, 7, '2023-02-18 20:32:22', 'lol', 1),
(68, 7, '2023-02-18 20:32:25', 'lol', 2),
(69, 7, '2023-02-18 20:32:29', 'lol', 3),
(70, 7, '2023-02-18 20:33:12', 'lol', 3),
(71, 7, '2023-02-18 20:33:16', 'lol2', 3),
(72, 7, '2023-02-18 20:34:47', 'lol3', 3),
(73, 7, '2023-02-18 20:37:47', 'Ayoo', 3),
(74, 8, '2023-02-18 20:38:08', 'Hey', 3),
(75, 7, '2023-02-18 20:38:13', 'Was geht', 3),
(76, 8, '2023-02-18 20:38:16', 'Nichts', 3),
(77, 8, '2023-02-18 20:38:22', 'Bei dir', 3),
(78, 7, '2023-02-18 20:38:44', 'Ich hab gerade dieses richtig abgefahrene Projekt gemacht ', 3),
(79, 8, '2023-02-18 20:38:52', 'Kuhl', 4),
(80, 8, '2023-02-18 20:38:59', 'Ist mir egal', 4),
(81, 7, '2023-02-18 20:39:29', 'ok bye', 4),
(82, 8, '2023-02-18 20:39:58', 'yo', 0),
(83, 11, '2023-02-18 20:40:02', 'Hi', 0),
(84, 11, '2023-02-18 20:40:09', 'Was geht?', 0),
(85, 8, '2023-02-18 20:40:21', 'Paul hat mich gerade angeschrieben', 0),
(86, 11, '2023-02-18 20:40:24', 'Mich auch', 0),
(87, 8, '2023-02-18 20:40:28', 'Echt?', 0),
(88, 11, '2023-02-18 20:40:31', 'Ja', 0),
(89, 11, '2023-02-18 20:40:39', 'Ich bin du', 0),
(90, 11, '2023-02-18 20:40:43', 'Vollidiot ', 0),
(91, 8, '2023-02-18 20:40:50', 'Understandable ', 0),
(92, 11, '2023-02-18 20:41:00', 'Have a nice day', 1),
(93, 8, '2023-02-18 20:41:04', 'Wait', 1),
(94, 8, '2023-02-18 20:41:10', 'Du bist nicht ich ', 1),
(95, 11, '2023-02-18 20:41:14', 'nicht?', 1),
(96, 8, '2023-02-18 20:41:17', 'nein', 1),
(97, 8, '2023-02-18 20:41:21', 'Du bist paul', 1),
(98, 8, '2023-02-18 20:41:24', 'Und ich auch', 1),
(99, 11, '2023-02-18 20:41:29', 'fuck', 1),
(100, 11, '2023-02-18 20:41:42', 'Ich will nicht mehr', 1),
(101, 11, '2023-02-18 20:41:49', 'Goodbye', 1),
(102, 8, '2023-02-18 20:41:57', 'Hab dich auch lieb ', 2),
(103, 11, '2023-02-18 20:42:09', 'Du meinst dich selbst?', 2),
(104, 8, '2023-02-18 20:42:15', 'Ich hab alle leib', 2),
(105, 7, '2023-02-18 20:43:07', 'Hello', 0),
(106, 7, '2023-02-18 20:43:12', 'Hello 2', 0),
(107, 15, '2023-02-18 20:48:41', 'Hi', 0),
(108, 7, '2023-02-18 20:48:45', 'yo', 0),
(109, 15, '2023-02-18 20:49:00', 'Arbeitest du gerade an deinem Informatikprojekt?', 0),
(110, 7, '2023-02-18 20:49:10', 'Ja', 0),
(111, 16, '2023-02-18 20:51:06', 'Hallo Paul', 0),
(112, 7, '2023-02-18 20:51:12', 'Hallo mama', 0),
(113, 22, '2023-02-19 11:07:00', 'yo', 0),
(114, 7, '2023-02-19 11:40:17', 'Hiiiii', 4),
(115, 8, '2023-02-19 11:40:25', 'Piss off', 4),
(116, 7, '2023-02-26 21:00:15', 'sup', 4),
(117, 7, '2023-03-19 23:53:42', 'AYO wasup mfer', 4),
(118, 8, '2023-03-19 23:56:17', 'Hi', 4),
(119, 8, '2023-03-19 23:58:52', 'fsdfgdfdsf', 4),
(120, 7, '2023-03-20 00:00:42', 'ghgdhdf', 4),
(121, 8, '2023-03-20 00:02:40', 'gdfgdfgdfg', 5),
(122, 7, '2023-03-20 00:05:18', 'fsdfsdfds', 5),
(123, 7, '2023-03-20 00:05:22', 'ddsa', 5),
(124, 7, '2023-03-20 00:05:28', 'fadsfsfdgsfgtrhejtehnetzhetznhtzzhehdszthbsfgbrez', 5);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `user`
--

CREATE TABLE `user` (
  `uid` int(11) NOT NULL,
  `firstname` text NOT NULL,
  `lastname` text NOT NULL,
  `email` text NOT NULL,
  `username` text NOT NULL,
  `password` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Hold all basic user information';

--
-- Daten für Tabelle `user`
--

INSERT INTO `user` (`uid`, `firstname`, `lastname`, `email`, `username`, `password`) VALUES
(7, 'Paul', 'Spiers', 'test@test.com', 'paul', 'lol'),
(8, 'Lukas', 'Fritz', 'lukas@test.com', 'lukas', 'lol'),
(9, 'Lukas', 'Fritz', 'lukas@test.com', 'lukas1', 'lol'),
(10, 'Lukas', 'Fritz', 'lukas@test.com', 'lukas2', 'lol'),
(11, 'Lukas', 'Fritz', 'lukas@test.com', 'lukas3', 'lol'),
(12, 'Paul', 'Spiers', 'paul@test.com', 'paul2', 'lol'),
(13, 'Paul', 'Spiers', 'paul@test.com', 'paul3', 'lol'),
(14, 'Paul', 'Spiers', 'paul@test.com', 'paul4', 'lol'),
(15, 'Joris', 'Ludwig', 'joris@test.com', 'joris', 'lol'),
(16, 'Cordula', 'Spiers', 'cordula@test.com', 'cordula', 'lol'),
(17, 'Paul', 'Spiers', 'paul@test.com', 'paul5', 'lol'),
(18, 'Paul', 'Spiers', 'test@test@com', 'paul6', 'lol'),
(19, 'fsfd', 'fsdfs', 'gsfgfs', 'paul9', 'lol'),
(20, 'fsgf', 'fdsgdsg', 'sfgfd', 'paul10', 'lol'),
(21, 'sfdsg', 'fsdfds', 'fgfdfs', 'paul11', 'lol'),
(22, 'fdsfds', 'sfgs', 'fsdfds', 'paul12', 'lol');

--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `directchat`
--
ALTER TABLE `directchat`
  ADD PRIMARY KEY (`cid`),
  ADD KEY `user1` (`user1`),
  ADD KEY `user2` (`user2`);

--
-- Indizes für die Tabelle `directmessage`
--
ALTER TABLE `directmessage`
  ADD PRIMARY KEY (`cid`,`mid`),
  ADD KEY `mid` (`mid`);

--
-- Indizes für die Tabelle `groupchat`
--
ALTER TABLE `groupchat`
  ADD PRIMARY KEY (`gcid`);

--
-- Indizes für die Tabelle `groupmessage`
--
ALTER TABLE `groupmessage`
  ADD KEY `gcid` (`gcid`),
  ADD KEY `mid` (`mid`);

--
-- Indizes für die Tabelle `message`
--
ALTER TABLE `message`
  ADD PRIMARY KEY (`mid`),
  ADD KEY `sender` (`sender`);

--
-- Indizes für die Tabelle `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`uid`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `directchat`
--
ALTER TABLE `directchat`
  MODIFY `cid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT für Tabelle `groupchat`
--
ALTER TABLE `groupchat`
  MODIFY `gcid` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT für Tabelle `message`
--
ALTER TABLE `message`
  MODIFY `mid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=125;

--
-- AUTO_INCREMENT für Tabelle `user`
--
ALTER TABLE `user`
  MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- Constraints der exportierten Tabellen
--

--
-- Constraints der Tabelle `directchat`
--
ALTER TABLE `directchat`
  ADD CONSTRAINT `directchat_ibfk_1` FOREIGN KEY (`user1`) REFERENCES `user` (`uid`),
  ADD CONSTRAINT `directchat_ibfk_2` FOREIGN KEY (`user2`) REFERENCES `user` (`uid`);

--
-- Constraints der Tabelle `directmessage`
--
ALTER TABLE `directmessage`
  ADD CONSTRAINT `directmessage_ibfk_1` FOREIGN KEY (`cid`) REFERENCES `directchat` (`cid`),
  ADD CONSTRAINT `directmessage_ibfk_2` FOREIGN KEY (`mid`) REFERENCES `message` (`mid`);

--
-- Constraints der Tabelle `groupmessage`
--
ALTER TABLE `groupmessage`
  ADD CONSTRAINT `groupmessage_ibfk_1` FOREIGN KEY (`gcid`) REFERENCES `groupchat` (`gcid`),
  ADD CONSTRAINT `groupmessage_ibfk_2` FOREIGN KEY (`mid`) REFERENCES `message` (`mid`);

--
-- Constraints der Tabelle `message`
--
ALTER TABLE `message`
  ADD CONSTRAINT `message_ibfk_1` FOREIGN KEY (`sender`) REFERENCES `user` (`uid`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
