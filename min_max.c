#include "postgres.h"
#include "fmgr.h"
#include "utils/array.h"
#include "utils/builtins.h"
#include "utils/float.h"
#include "utils/varlena.h"
#include "utils/guc.h"
#include "catalog/pg_type_d.h"

#define INITIAL_STRING "-1"
#define INITIAL_INT 0
#define INITIAL_FLOAT (float8) 0

PG_MODULE_MAGIC;

char *separator = NULL;

extern void _PG_init(void);
extern Datum min_max_int2(PG_FUNCTION_ARGS);
extern Datum min_max_int2_to_string(PG_FUNCTION_ARGS);
extern Datum min_max_int4(PG_FUNCTION_ARGS);
extern Datum min_max_int4_to_string(PG_FUNCTION_ARGS);
extern Datum min_max_int8(PG_FUNCTION_ARGS);
extern Datum min_max_int8_to_string(PG_FUNCTION_ARGS);
extern Datum min_max_float4(PG_FUNCTION_ARGS);
extern Datum min_max_float4_to_string(PG_FUNCTION_ARGS);
extern Datum min_max_float8(PG_FUNCTION_ARGS);
extern Datum min_max_float8_to_string(PG_FUNCTION_ARGS);

//extern Datum min_max_text(PG_FUNCTION_ARGS);
//extern Datum min_max_text_to_string(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(min_max_int2);

Datum 
min_max_int2(PG_FUNCTION_ARGS)
{
	ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
	int16 new_val = PG_GETARG_INT16(1);
	int16 *trans_values;

	trans_values = (int16 *) ARR_DATA_PTR(trans_array);

	if(trans_values[0] == INITIAL_INT && trans_values[1] == INITIAL_INT)
                trans_values[0] = trans_values[1] = new_val;
        else if(new_val < trans_values[0])
                trans_values[0] = new_val;
        else if(new_val > trans_values[1])
                trans_values[1] = new_val;

        PG_RETURN_ARRAYTYPE_P(trans_array);
}

PG_FUNCTION_INFO_V1(min_max_int2_to_string);

Datum
min_max_int2_to_string(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        int16 *trans_values = (int16 *) ARR_DATA_PTR(trans_array);
        text *result;
        char *str;

        /*Just make cstring by psprintf function and then convert it to text*/
        str = psprintf("%d%s%d", trans_values[0], separator, trans_values[1]);
        result = cstring_to_text(str);
        pfree(str);
        PG_RETURN_TEXT_P(result);
}

PG_FUNCTION_INFO_V1(min_max_int4);

Datum
min_max_int4(PG_FUNCTION_ARGS)
{
	ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
	int32 new_val = PG_GETARG_INT32(1);
	int32 *trans_values;

	trans_values = (int32 *) ARR_DATA_PTR(trans_array);

	/* We need to track minumum and maximum, therefore, an array could be used for that. 
         * On the first step array is {0,0}, so we can initialize two values as newval
	 * transvalues[0] stores the minimum and transvalues[1] stores the maximum*/
	if(trans_values[0] == INITIAL_INT && trans_values[1] == INITIAL_INT)
		trans_values[0] = trans_values[1] = new_val;
	else if(new_val < trans_values[0])
		trans_values[0] = new_val;
	else if(new_val > trans_values[1])
		trans_values[1] = new_val;

	PG_RETURN_ARRAYTYPE_P(trans_array);
}

PG_FUNCTION_INFO_V1(min_max_int4_to_string);

Datum
min_max_int4_to_string(PG_FUNCTION_ARGS)
{
	ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
	int32 *trans_values = (int32 *) ARR_DATA_PTR(trans_array);
	text *result;
	char *str;

	/*Just make cstring by psprintf function and then convert it to text*/
	str = psprintf("%d%s%d", trans_values[0], separator, trans_values[1]);
	result = cstring_to_text(str);
	pfree(str);
	PG_RETURN_TEXT_P(result);
}

PG_FUNCTION_INFO_V1(min_max_int8);

Datum
min_max_int8(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        int64 new_val = PG_GETARG_INT64(1);
        int64 *trans_values;

        trans_values = (int64 *) ARR_DATA_PTR(trans_array);

        /* We need to track minumum and maximum, therefore, an array could be used for that.
         * On the first step array is {0,0}, so we can initialize two values as newval
         * transvalues[0] stores the minimum and transvalues[1] stores the maximum*/
        if(trans_values[0] == INITIAL_INT && trans_values[1] == INITIAL_INT)
                trans_values[0] = trans_values[1] = new_val;
        else if(new_val < trans_values[0])
                trans_values[0] = new_val;
        else if(new_val > trans_values[1])
                trans_values[1] = new_val;

        PG_RETURN_ARRAYTYPE_P(trans_array);
}

PG_FUNCTION_INFO_V1(min_max_int8_to_string);

Datum
min_max_int8_to_string(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        int64 *trans_values = (int64 *) ARR_DATA_PTR(trans_array);
        text *result;
        char *str;

        /*Just make cstring by psprintf function and then convert it to text*/
        str = psprintf("%ld%s%ld", trans_values[0], separator, trans_values[1]);
        result = cstring_to_text(str);
        pfree(str);
        PG_RETURN_TEXT_P(result);
}

PG_FUNCTION_INFO_V1(min_max_float4);

Datum
min_max_float4(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        float4 new_val = PG_GETARG_FLOAT4(1);
        float4 *trans_values = (float4 *) ARR_DATA_PTR(trans_array);

        if(float4_cmp_internal(trans_values[0], INITIAL_FLOAT) == 0 && float4_cmp_internal(trans_values[1], INITIAL_FLOAT) == 0)
                trans_values[0] = trans_values[1] = new_val;

        if(float4_cmp_internal(new_val, trans_values[0]) == -1)
                trans_values[0] = new_val;
        else if(float4_cmp_internal(new_val, trans_values[0]) == 1)
                trans_values[1] = new_val;

        PG_RETURN_ARRAYTYPE_P(trans_array);
}


PG_FUNCTION_INFO_V1(min_max_float4_to_string);

Datum
min_max_float4_to_string(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        float4 *trans_values = (float4 *) ARR_DATA_PTR(trans_array);
        text *result;
        char *str;

        /*Just make cstring by psprintf function and then convert it to text*/
        str = psprintf("%.6f%s%.6f", trans_values[0], separator, trans_values[1]);
        result = cstring_to_text(str);
        pfree(str);
        PG_RETURN_TEXT_P(result);
}

PG_FUNCTION_INFO_V1(min_max_float8);

Datum
min_max_float8(PG_FUNCTION_ARGS)
{
	ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
	float8 new_val = PG_GETARG_FLOAT8(1);
	float8 *trans_values = (float8 *) ARR_DATA_PTR(trans_array);
	
	if(float8_cmp_internal(trans_values[0], INITIAL_FLOAT) == 0 && float8_cmp_internal(trans_values[1], INITIAL_FLOAT) == 0)
		trans_values[0] = trans_values[1] = new_val;

        if(float8_cmp_internal(new_val, trans_values[0]) == -1)
		trans_values[0] = new_val;
	else if(float8_cmp_internal(new_val, trans_values[0]) == 1)
		trans_values[1] = new_val;

	PG_RETURN_ARRAYTYPE_P(trans_array);
}


PG_FUNCTION_INFO_V1(min_max_float8_to_string);

Datum
min_max_float8_to_string(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        float8 *trans_values = (float8 *) ARR_DATA_PTR(trans_array);
        text *result;
        char *str;

        /*Just make cstring by psprintf function and then convert it to text*/
        str = psprintf("%.6f%s%.6f", trans_values[0], separator, trans_values[1]);
        result = cstring_to_text(str);
        pfree(str);
        PG_RETURN_TEXT_P(result);
}

void
_PG_init(void)
{
	DefineCustomStringVariable("min_max.separator",
									"A string for separating min and max",
									NULL,
									&separator,
									" -> ",
									PGC_USERSET,
									0,
									NULL,
									NULL, NULL);
}

/*PG_FUNCTION_INFO_V1(min_max_text);

Datum 
min_max_text(PG_FUNCTION_ARGS)
{
	ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
	text *txt = PG_GETARG_TEXT_PP(1);
	int txt_size = VARSIZE_ANY_EXHDR(txt);
	Datum *trans_datums;
	bool *trans_nulls; 
	int trans_count;
	char *min_str, *max_str, *new_val;

	deconstruct_array(trans_array, TEXTOID, -1, false, 'i', &trans_datums, &trans_nulls, &trans_count);	

	min_str = VARDATA(trans_datums[0]);
	max_str = VARDATA(trans_datums[1]);
	new_val = text_to_cstring((const text *)txt);

	if(strcmp(min_str, INITIAL_STRING) == 0 && strcmp(max_str, INITIAL_STRING) == 0)
		trans_datums[0] = trans_datums[1] = PointerGetDatum(txt);
	else if(varstr_cmp(new_val, txt_size, min_str, VARSIZE(trans_datums[0]) - VARHDRSZ, 
				PG_GET_COLLATION()) == -1)
		trans_datums[0] = PointerGetDatum(txt);
	else if(varstr_cmp(new_val, txt_size, max_str, VARSIZE(trans_datums[1]) - VARHDRSZ,
                                PG_GET_COLLATION()) == 1)
		trans_datums[1] = PointerGetDatum(txt);
	
	trans_array = construct_array(trans_datums, 2, TEXTOID, -1, false, 'i');
	pfree(new_val);
	pfree(trans_nulls);
	pfree(trans_datums);
	PG_RETURN_ARRAYTYPE_P(trans_array);
}

PG_FUNCTION_INFO_V1(min_max_text_to_string);

Datum
min_max_text_to_string(PG_FUNCTION_ARGS)
{
        ArrayType *trans_array = PG_GETARG_ARRAYTYPE_P(0);
        Datum *trans_datums;
	int trans_count, min_str_size, max_str_size, result_size;
	int sep_len = strlen(separator);
	text *result;

	deconstruct_array(trans_array, TEXTOID, -1, false, 'i', &trans_datums, NULL, &trans_count);
	min_str_size = VARSIZE(trans_datums[0]) - VARHDRSZ;
    	max_str_size = VARSIZE(trans_datums[1]) - VARHDRSZ;
	result_size = min_str_size + max_str_size + VARHDRSZ;
	result = (text *) palloc(result_size);

	SET_VARSIZE(result, result_size);
	memcpy(VARDATA(result), VARDATA_ANY(trans_datums[0]), min_str_size);
	memcpy(VARDATA(result) + min_str_size, separator, sep_len);
	memcpy(VARDATA(result) + min_str_size + sep_len, VARDATA_ANY(trans_datums[1]), max_str_size);
 
	pfree(trans_datums);
        PG_RETURN_TEXT_P(result);
}
*/
