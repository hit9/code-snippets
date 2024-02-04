CREATE TABLE IF NOT EXISTS t1 (
    id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    a int DEFAULT 0 NOT NULL,
    b varchar(255) DEFAULT '' NOT NULL,
    c BOOLEAN DEFAULT FALSE NOT NULL,
    d int DEFAULT 0 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

create index a on t1 (a);
create index b on t1 (b);
