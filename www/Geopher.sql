CREATE TABLE location (
       id MEDIUMINT(8) UNSIGNED NOT NULL AUTO_INCREMENT,
       glat DECIMAL(10,8) NOT NULL,
       glon DECIMAL(11,8) NOT NULL,
       name VARCHAR(1024) NOT NULL,
       service VARCHAR(1024) NOT NULL,
       schedule TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
       message VARCHAR(1024),
       location VARCHAR(1024),
       PRIMARY KEY (id)
);

CREATE TABLE rating (
       id MEDIUMINT(8) UNSIGNED NOT NULL AUTO_INCREMENT,
       name VARCHAR(1024),
       push TINYINT(1),
       pull TINYINT(1),
       vote MEDIUMINT(8),
       rating DECIMAL(5,4),
       PRIMARY KEY (id)
);

CREATE TABLE override (
       id MEDIUMINT(8) UNSIGNED NOT NULL AUTO_INCREMENT,
       name VARCHAR(1024),
       word JSON,
       bidprice DECIMAL(10,8) NOT NULL,
       buy DECIMAL(10,8) NOT NULL,
       sell DECIMAL(10,8) NOT NULL,
       owner VARCHAR(1024) NOT NULL,
       override VARCHAR(1024) NOT NULL,
       PRIMARY KEY (id)
);
