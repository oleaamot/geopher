--DROP TABLE Geophere;
--DROP TABLE Price;
--DROP TABLE Link;
--DROP TABLE Schedule;
--DROP TABLE Positron;

CREATE TABLE Positron (
       glat DECIMAL(8,6),
       glon DECIMAL(9,6),
       alt DECIMAL(9,6),
       w DECIMAL(9,6),
       h DECIMAL(9,6),
       l DECIMAL(9,6),
       re DECIMAL(9,6)
);

CREATE TABLE Schedule (
       created TIMESTAMP,
       expires TIMESTAMP,
       updated TIMESTAMP,
       PRIMARY KEY (created)
);

CREATE TABLE Link (
       protocol TEXT,
       location TEXT
);

CREATE TABLE Price (
       currency TEXT,
       ask DECIMAL(9,6),
       bid DECIMAL(9,6),
       fix DECIMAL(9,6)
);

CREATE TABLE Geopher (
       actionid INT4 NOT NULL AUTO_INCREMENT PRIMARY KEY,
       movement TEXT,
       glat DECIMAL(8,6) REFERENCES Positron (glat),
       glon DECIMAL(9,6) REFERENCES Positron (glon),
       galt DECIMAL(9,6) REFERENCES Positron (galt),       
       created TIMESTAMP REFERENCES Schedule(created),
       expires TIMESTAMP REFERENCES Schedule(expires),
       updated TIMESTAMP REFERENCES Schedule(updated),
       protocol TEXT REFERENCES Link(protocol),
       location TEXT REFERENCES Link(location),
       currency TEXT REFERENCES Price(currency),
       ask DECIMAL(9,6) REFERENCES Price(ask),
       bid DECIMAL(9,6) REFERENCES Price(bid),
       fix DECIMAL(9,6) REFERENCES Price(fix)
);
