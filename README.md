# min_max
min_max - a simple extension that calculates the minumum and the maximum amongst smallint, int, bigint, float4, float8 values

This extension allows you to find out the minumum and the maximum amongst smallint, int, bigint, float4, float8 values

It is possible by using custom aggregate engine. For that a transition function and a final function must be written.

The transition function allows you to accumulate the values and the final function is requried for constructing a final text value

Then we can use CREATE AGGREGATE to build a new aggregate

You can build this extension by using the following commands

sudo make USE_PGXS=1 PG_CONFIG=path_to_pg_binaries/pg_config install

Then run the following command path_to_psql/psql -U postgres -d db_name -c "CREATE EXTENSION min_max"

# GUC variables

min_max.separator - use it to change the final output. The example is provided below

test=# SELECT min_to_max(val) FROM (VALUES(5),(3),(6),(7),(9),(10),(7)) t(val);
 min_to_max
------------
 3 -> 10
(1 row)

test=# set min_max.separator to ' : ';
SET
UFOS_TSE=# SELECT min_to_max(val) FROM (VALUES(5),(3),(6),(7),(9),(10),(7)) t(val);
 min_to_max
------------
 3 : 10
(1 row)