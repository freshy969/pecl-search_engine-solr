/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2015 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author:                                                              |
   |          Omar Shaban <omars@php.net>                                 |
   +----------------------------------------------------------------------+
*/

#include "php_solr.h"

/* {{{ proto void SolrFunction::__construct([string field])
   Constructor. */
PHP_METHOD(SolrCollapseFunction, __construct)
{
    long int index = SOLR_UNIQUE_FUNCTION_INDEX();
    uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;
    solr_function_t *solr_function_dest = NULL;
    solr_function_t solr_function;
    zval *objptr = getThis();

    solr_char_t *param_name = (solr_char_t *)"field";
    COMPAT_ARG_SIZE_T param_name_len = sizeof("field");

    solr_string_t field_str;

    solr_char_t *field_name = NULL;
    int field_name_len = 0;

    memset(&solr_function, 0, sizeof(solr_function_t));

    if ((solr_function_dest = zend_hash_index_update_ptr(SOLR_GLOBAL(functions),index,(void *) &solr_function)) == NULL)
    {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error while registering query parameters in HashTable");

        return ;
    }
    zend_update_property_long(solr_ce_SolrCollapseFunction, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, index TSRMLS_CC);

    solr_function_dest->function_index = index;
    solr_function_dest->name_length = strlen("collapse");

    solr_function_dest->name = (solr_char_t *)"collapse";

    /* Allocated memory for the params HashTable using fast cache for HashTables */
    ALLOC_HASHTABLE(solr_function_dest->params);
    zend_hash_init(solr_function_dest->params, nSize, NULL, (dtor_func_t) solr_string_free_ex, SOLR_FUNCTIONS_PERSISTENT);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error Parsing Parameters");
        return;
    }

    if (field_name_len > 0 ){
        memset(&field_str, 0, sizeof(solr_string_t));
        solr_string_set(&field_str, (solr_char_t *)field_name, field_name_len);
        if (zend_hash_str_update_ptr(solr_function_dest->params, param_name, param_name_len, (void **)&field_str) == NULL) {
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        }
    }

    Z_OBJ_HT_P(getThis()) = &solr_collapse_function_object_handlers;
}
/* }}} */

/* {{{ proto void SolrFunction::__destruct(void)
   Destructor. */
PHP_METHOD(SolrCollapseFunction, __destruct)
{
    solr_function_t *function = NULL;
    /* Retrieve the document entry for this SolrDocument */
    if (solr_fetch_function_entry(getThis(), &function TSRMLS_CC) == SUCCESS )
    {
        zend_hash_index_del(SOLR_GLOBAL(functions), function->function_index);
    }

    return;
}

/* {{{ proto string SolrFunction::setField(string field)
  Set the field that is being collapsed on. The field must be a single valued String, Int or Float. */
PHP_METHOD(SolrCollapseFunction, setField)
{
    solr_char_t *key = "field", *arg;
    COMPAT_ARG_SIZE_T key_len = sizeof("field"), arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        RETURN_NULL();
    }

    if (solr_solrfunc_update_string(getThis(), key, key_len, (solr_char_t *)arg, arg_len TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{ proto string SolrFunction::getField(void)
  Get Collapse Field */
PHP_METHOD(SolrCollapseFunction, getField)
{
    solr_char_t *key = "field";
    int key_len = sizeof("field");

    solr_solrfunc_display_string(getThis(), key, key_len, &return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto string SolrFunction::setMin(string value)
  Selects the group heads by the min value of a numeric field or function query. */
PHP_METHOD(SolrCollapseFunction, setMin)
{
    solr_char_t *key = "min", *arg;
    int key_len = sizeof("min"), arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        RETURN_NULL();
    }

    if (solr_solrfunc_update_string(getThis(), key, key_len, (solr_char_t *)arg, arg_len TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto string SolrFunction::setMax(string value)
  Selects the group heads by the max value of a numeric field or function query. */
PHP_METHOD(SolrCollapseFunction, setMax)
{
    solr_char_t *key = "max", *arg;
    int key_len = sizeof("max"), arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        RETURN_NULL();
    }

    if (solr_solrfunc_update_string(getThis(), key, key_len, (solr_char_t *)arg, arg_len TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto string SolrFunction::getMin(void)
  Get min parameter */
PHP_METHOD(SolrCollapseFunction, getMin)
{
    solr_char_t *key = "min";
    int key_len = sizeof("min");

    solr_solrfunc_display_string(getThis(), key, key_len, &return_value TSRMLS_CC);
}
/* }}} */


/* {{{ proto string SolrFunction::getMax(void)
  Get max parameter */
PHP_METHOD(SolrCollapseFunction, getMax)
{
    solr_char_t *key = "max";
    int key_len = sizeof("max");

    solr_solrfunc_display_string(getThis(), key, key_len, &return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto string SolrFunction::setSize(void)
  Sets the initial size of the collapse data structures when collapsing on a numeric field only */
PHP_METHOD(SolrCollapseFunction, setSize)
{
    solr_char_t *key = "size", *arg;
    int key_len = sizeof("size"), arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        RETURN_NULL();
    }

    if (solr_solrfunc_update_string(getThis(), key, key_len, (solr_char_t *)arg, arg_len TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto string SolrFunction::getSize(void)
  Get size parameter */
PHP_METHOD(SolrCollapseFunction, getSize)
{
    solr_char_t *key = "size";
    int key_len = sizeof("size");

    solr_solrfunc_display_string(getThis(), key, key_len, &return_value TSRMLS_CC);
}
/* }}} */


/* {{{ proto string SolrFunction::setHint(void)
  Set collapse hint
  Currently there is only one hint available "top_fc", which stands for top level FieldCache */
PHP_METHOD(SolrCollapseFunction, setHint)
{
    solr_char_t *key = "hint", *arg;
    int key_len = sizeof("hint"), arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        RETURN_NULL();
    }

    if (solr_solrfunc_update_string(getThis(), key, key_len, (solr_char_t *)arg, arg_len TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto string SolrFunction::getHint(void)
  Get Hint */
PHP_METHOD(SolrCollapseFunction, getHint)
{
    solr_char_t *key = "hint";
    int key_len = sizeof("hint");

    solr_solrfunc_display_string(getThis(), key, key_len, &return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto string SolrFunction::setNullPolicy(void)
  Sets the NULL Policy. Accepts ignore, expand, or collapse */
PHP_METHOD(SolrCollapseFunction, setNullPolicy)
{
    solr_char_t *key = "nullPolicy", *arg;
    int key_len = sizeof("nullPolicy"), arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        RETURN_NULL();
    }

    if (solr_solrfunc_update_string(getThis(), key, key_len, (solr_char_t *)arg, arg_len TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error assigning field");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto string SolrFunction::getNullPolicy(void)
  Get NullPolicy */
PHP_METHOD(SolrCollapseFunction, getNullPolicy)
{
    solr_char_t *key = "nullPolicy";
    int key_len = sizeof("nullPolicy");

    solr_solrfunc_display_string(getThis(), key, key_len, &return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto string SolrFunction::__toString(void)
  String value of the function object */
PHP_METHOD(SolrCollapseFunction, __toString)
{
    solr_function_t *collapse_func;
    solr_string_t *buffer = NULL;

    if(solr_fetch_function_entry(getThis(), &collapse_func TSRMLS_CC) == FAILURE) {
        RETURN_NULL();
    }

    buffer = (solr_string_t *)emalloc(sizeof(solr_string_t));
    memset(buffer, 0, sizeof(solr_string_t));

    solr_solrfunc_to_string(collapse_func, &buffer);
    ZVAL_STRINGL(return_value, buffer->str, buffer->len);
    efree(buffer);
}
/* }}} */

/* {{{ proto SolrClient::__sleep(void)
   Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrCollapseFunction, __sleep)
{
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Serialization of SolrCollapseFunction objects is currently not supported");
}
/* }}} */

/* {{{ proto SolrClient::__wakeup(void)
   Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrCollapseFunction, __wakeup)
{
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unserialization of SolrCollapseFunction objects is currently not supported");
}
/* }}} */

/* {{{ throw exception on cloning (clone handler) */
zend_object* solr_collapse_function_handlers_clone_object(zval *object TSRMLS_DC)
{
    zend_object *fake;
    fake = zend_objects_new(solr_ce_SolrCollapseFunction);
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_4001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Cloning of SolrCollapseFunction objects is currently not supported");
    return fake;
}
/* }}} */


