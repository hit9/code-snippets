# 执行它以创建测试数据
# db 名字: testdb

import glob
import logging
import random
import string
from typing import Callable

import MySQLdb

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[logging.StreamHandler()],
)

logger = logging.getLogger(__name__)

conn = MySQLdb.connect(
    host="127.0.0.1",
    user="root",
    port=3306,
    password="test",
    database="testdb",
    charset="utf8mb4",
    autocommit=False,
)


def gen_rand_string(n: int) -> str:
    chars = ""
    chars += string.ascii_lowercase
    chars += string.digits
    return "".join([random.choice(chars) for _ in range(n)])


def batch_insert(
    n: int, table: str, insert_statment: str, row_generator: Callable, step: int = 1000
) -> None:
    conn.cursor().execute(open(f"sqls/tables/{table}.sql", "r").read())

    conn.cursor().execute("TRUNCATE TABLE {};".format(table))
    conn.commit()

    cnt = 0
    while cnt < n:
        rows = []
        for _ in range(step):
            rows.append(row_generator())
            if cnt >= n:
                break
            cnt += 1
        cur = conn.cursor()
        cur.executemany(insert_statment, rows)
        conn.commit()
        logger.info("insert {0} {1}".format(table, cnt))


def gen_data_table_t1(n: int, step: int = 1000) -> None:
    batch_insert(
        n,
        "t1",
        "INSERT INTO t1 (a, b, c, d) VALUES (%s, %s, %s, %s);",
        lambda: (
            random.randint(1, 100),
            gen_rand_string(32),
            random.randint(0, 1),
            random.randint(1, 100),
        ),
        step=step,
    )


def gen_data_table_t2(n: int, step: int = 1000) -> None:
    batch_insert(
        n,
        "t2",
        "INSERT INTO t2 (a, b, c) VALUES (%s, %s, %s);",
        lambda: (
            random.randint(1, 100),
            gen_rand_string(32),
            random.randint(1, 100),
        ),
        step=step,
    )


def gen() -> None:
    gen_data_table_t1(1000000, step=10000)
    gen_data_table_t2(1000000, step=10000)


def main():
    logger.info("recreating db")
    conn.cursor().execute("drop database testdb;")
    conn.cursor().execute("create database testdb;")
    conn.cursor().execute("use testdb;")
    gen()


if __name__ == "__main__":
    main()
