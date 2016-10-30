-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 07, 2015 at 02:47 PM
-- Server version: 5.5.43-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `gestionecole`
--

-- --------------------------------------------------------

--
-- Table structure for table `Abonnement`
--

CREATE TABLE IF NOT EXISTS `Abonnement` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_Dossier` int(11) NOT NULL,
  `id_Echeance` int(11) NOT NULL,
  `id_Prestation` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_Dossier` (`id_Dossier`),
  KEY `id_Echeance` (`id_Echeance`),
  KEY `id_Prestation` (`id_Prestation`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=40 ;

--
-- Dumping data for table `Abonnement`
--

INSERT INTO `Abonnement` (`id`, `id_Dossier`, `id_Echeance`, `id_Prestation`) VALUES
(15, 201500002, 1, 1),
(17, 201500002, 1, 1),
(18, 201500002, 1, 1),
(19, 201500002, 1, 1),
(25, 201500003, 9, 2),
(30, 201500002, 2, 3),
(31, 201500002, 3, 3),
(32, 201500002, 4, 3),
(33, 201500003, 4, 3),
(34, 201500001, 6, 2),
(36, 201500001, 9, 3),
(37, 201500001, 10, 3),
(38, 201500001, 11, 3),
(39, 201500001, 12, 3);

-- --------------------------------------------------------

--
-- Table structure for table `Adresse`
--

CREATE TABLE IF NOT EXISTS `Adresse` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `adresseLigne1` varchar(120) NOT NULL,
  `adresseLigne2` varchar(120) NOT NULL,
  `ville` varchar(20) NOT NULL,
  `codePostale` int(4) NOT NULL,
  `pays` varchar(30) NOT NULL,
  `type` tinyint(1) NOT NULL,
  `id_Parent` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_Parent` (`id_Parent`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=21 ;

--
-- Dumping data for table `Adresse`
--

INSERT INTO `Adresse` (`id`, `adresseLigne1`, `adresseLigne2`, `ville`, `codePostale`, `pays`, `type`, `id_Parent`) VALUES
(1, 'N26 rue de palastine', '', 'Gafsa', 2100, 'Tunisie', 1, 20),
(2, '', '', '', 0, 'Tunisie', 0, 20),
(3, 'N26 rue de palastine', '', 'Gafsa', 2100, 'Tunisie', 1, 21),
(4, 'école aljoumhouriya', '', 'Gafsa', 2100, 'Tunisie', 0, 21),
(5, 'x', 'x', 'x', 0, 'Tunisie', 1, 22),
(6, '', '', '', 0, 'Tunisie', 0, 22),
(7, 'N26 rue de la republique', '', 'Mehdia', 4000, 'Tunisie', 1, 23),
(8, '', '', '', 0, 'Tunisie', 0, 23),
(9, 'x', 'x', 'Monastir', 0, 'Tunisie', 1, 24),
(10, '', '', '', 0, 'Tunisie', 0, 24),
(11, 'x', 'x', 'x', 0, 'Tunisie', 1, 25),
(12, '', '', '', 0, 'Tunisie', 0, 25),
(13, '', '', '', 0, 'Tunisie', 1, 26),
(14, '', '', '', 0, 'Tunisie', 0, 26),
(15, '', '', '', 0, 'Tunisie', 1, 27),
(16, '', '', '', 0, 'Tunisie', 0, 27),
(17, 'Tafella', '', 'Sousse', 4000, 'Tunisie', 1, 28),
(18, 'Bouhsina', '', 'Sousse', 4000, 'Tunisie', 0, 28),
(19, 'x', 'x', 'x', 0, 'Tunisie', 1, 29),
(20, 'y', 'y', 'y', 0, 'Tunisie', 0, 29);

-- --------------------------------------------------------

--
-- Table structure for table `Dossier`
--

CREATE TABLE IF NOT EXISTS `Dossier` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(50) NOT NULL,
  `prenom` varchar(50) NOT NULL,
  `id_Niveau` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_Niveau` (`id_Niveau`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=201500004 ;

--
-- Dumping data for table `Dossier`
--

INSERT INTO `Dossier` (`id`, `nom`, `prenom`, `id_Niveau`) VALUES
(201500001, 'Lotfi', 'Messaoudi', 1),
(201500002, 'Oussema', 'Dallel', 1),
(201500003, 'Belgacem', 'Faycel', 1);

-- --------------------------------------------------------

--
-- Table structure for table `Echeances`
--

CREATE TABLE IF NOT EXISTS `Echeances` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(40) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

--
-- Dumping data for table `Echeances`
--

INSERT INTO `Echeances` (`id`, `nom`) VALUES
(1, 'Janvier'),
(2, 'Février'),
(3, 'Mars'),
(4, 'Avril'),
(5, 'Mai'),
(6, 'Juin'),
(7, 'Juillet'),
(8, 'Aout'),
(9, 'Septembre'),
(10, 'Octobre'),
(11, 'Novembre'),
(12, 'Décembre');

-- --------------------------------------------------------

--
-- Table structure for table `Niveau`
--

CREATE TABLE IF NOT EXISTS `Niveau` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `niveau` varchar(40) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `Niveau`
--

INSERT INTO `Niveau` (`id`, `niveau`) VALUES
(1, '1ére année'),
(2, '2éme année');

-- --------------------------------------------------------

--
-- Table structure for table `Parent`
--

CREATE TABLE IF NOT EXISTS `Parent` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(50) NOT NULL,
  `prenom` varchar(50) NOT NULL,
  `profession` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=30 ;

--
-- Dumping data for table `Parent`
--

INSERT INTO `Parent` (`id`, `nom`, `prenom`, `profession`) VALUES
(20, 'Hedi', 'Messaoudi', 'Retraité'),
(21, 'Najette', 'Dakhlaoui', 'Maîtresse'),
(22, 'Mehrez', 'Dallel', 'Professeur'),
(23, 'Oumayma', 'Fadhel', 'Pas de travaille'),
(24, 'Belgacem', 'Monji', 'Ing'),
(25, 'Nayli', 'Mounira', '--'),
(26, '', '', ''),
(27, '', '', ''),
(28, 'BouMohamed', 'BouMohamed', 'Prof'),
(29, 'OmMohamed2', 'OmMohamed', 'Enseignante');

-- --------------------------------------------------------

--
-- Table structure for table `Prestation`
--

CREATE TABLE IF NOT EXISTS `Prestation` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `Prestation`
--

INSERT INTO `Prestation` (`id`, `nom`) VALUES
(1, 'Restoration'),
(2, 'Transport'),
(3, 'Logement');

-- --------------------------------------------------------

--
-- Table structure for table `Responsabilite`
--

CREATE TABLE IF NOT EXISTS `Responsabilite` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_Parent1` int(11) NOT NULL,
  `id_Parent2` int(11) NOT NULL,
  `id_Dossier` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_Parent1` (`id_Parent1`),
  KEY `id_Parent2` (`id_Parent2`),
  KEY `id_Dossier` (`id_Dossier`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Dumping data for table `Responsabilite`
--

INSERT INTO `Responsabilite` (`id`, `id_Parent1`, `id_Parent2`, `id_Dossier`) VALUES
(13, 20, 21, 201500001),
(14, 22, 23, 201500002),
(15, 24, 25, 201500003);

-- --------------------------------------------------------

--
-- Table structure for table `Tel`
--

CREATE TABLE IF NOT EXISTS `Tel` (
  `numTel` int(8) NOT NULL AUTO_INCREMENT,
  `id_Parent` int(11) NOT NULL,
  PRIMARY KEY (`numTel`),
  KEY `id_Parent` (`id_Parent`),
  KEY `id_Parent_2` (`id_Parent`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=92544514 ;

--
-- Dumping data for table `Tel`
--

INSERT INTO `Tel` (`numTel`, `id_Parent`) VALUES
(92544510, 20),
(23613526, 21),
(58785896, 22),
(87896545, 23),
(92544511, 24),
(5020100, 25),
(92544512, 26),
(92544513, 27),
(50201080, 28),
(50408060, 29);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `Abonnement`
--
ALTER TABLE `Abonnement`
  ADD CONSTRAINT `Abonnement_ibfk_1` FOREIGN KEY (`id_Dossier`) REFERENCES `Dossier` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `Abonnement_ibfk_2` FOREIGN KEY (`id_Echeance`) REFERENCES `Echeances` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `Abonnement_ibfk_3` FOREIGN KEY (`id_Prestation`) REFERENCES `Prestation` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `Adresse`
--
ALTER TABLE `Adresse`
  ADD CONSTRAINT `contrainteDeAdresse` FOREIGN KEY (`id_Parent`) REFERENCES `Parent` (`id`);

--
-- Constraints for table `Dossier`
--
ALTER TABLE `Dossier`
  ADD CONSTRAINT `contrainteDeNiveau` FOREIGN KEY (`id_Niveau`) REFERENCES `Niveau` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `Responsabilite`
--
ALTER TABLE `Responsabilite`
  ADD CONSTRAINT `ContrainteDossier` FOREIGN KEY (`id_Dossier`) REFERENCES `Dossier` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `ContrainteParent1` FOREIGN KEY (`id_Parent1`) REFERENCES `Parent` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `ContrainteParent2` FOREIGN KEY (`id_Parent2`) REFERENCES `Parent` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `Tel`
--
ALTER TABLE `Tel`
  ADD CONSTRAINT `contrainteDeTel` FOREIGN KEY (`id_Parent`) REFERENCES `Parent` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
