\echo Use "CREATE EXTENSION min_max" to load this file. \quit

CREATE FUNCTION min_max_int2(smallint[], smallint)
RETURNS smallint[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_int2_to_string(smallint[])
RETURNS text AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_int4(int[], int) 
RETURNS int[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_int4_to_string(int[])
RETURNS text AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_int8(bigint[], bigint)
RETURNS bigint[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_int8_to_string(bigint[])
RETURNS text AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_float4(float4[], float4)
RETURNS float4[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_float4_to_string(float4[])
RETURNS text AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_float8(float8[], float8)
RETURNS float8[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_float8_to_string(float8[])
RETURNS text AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE AGGREGATE min_to_max(smallint)
(
    sfunc = min_max_int2,
    stype = smallint[],
    finalfunc = min_max_int2_to_string,
    initcond = '{0,0}'
);

CREATE AGGREGATE min_to_max(int)
(
    sfunc = min_max_int4,
    stype = int[],
    finalfunc = min_max_int4_to_string,
    initcond = '{0,0}'
);

CREATE AGGREGATE min_to_max(bigint)
(
    sfunc = min_max_int8,
    stype = bigint[],
    finalfunc = min_max_int8_to_string,
    initcond = '{0,0}'
);

CREATE AGGREGATE min_to_max(float4)
(
    sfunc = min_max_float4,
    stype = float4[],
    finalfunc = min_max_float4_to_string,
    initcond = '{0,0}'
);

CREATE AGGREGATE min_to_max(float8)
(
    sfunc = min_max_float8,
    stype = float8[],
    finalfunc = min_max_float8_to_string,
    initcond = '{0,0}'
);

/*CREATE FUNCTION min_max_text(text[], text)
RETURNS text[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION min_max_text_to_string(text[])
RETURNS text[] AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE AGGREGATE min_to_max(text)
(
    sfunc = min_max_text,
    stype = text[],
    finalfunc = min_max_text_to_string,
    initcond = '{"-1", "-1"}'
);*/
