
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "xxexcel.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *xxexcel_reader_ce;
zend_class_entry *xxexcel_writer_ce;

ZEND_DECLARE_MODULE_GLOBALS(xxexcel)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(xxexcel)
{
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(XxExcel_Reader);
	ZEPHIR_INIT(XxExcel_Writer);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(xxexcel)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_xxexcel_globals *xxexcel_globals TSRMLS_DC)
{
	xxexcel_globals->initialized = 0;

	/* Memory options */
	xxexcel_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	xxexcel_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	xxexcel_globals->cache_enabled = 1;

	/* Recursive Lock */
	xxexcel_globals->recursive_lock = 0;

	/* Static cache */
	memset(xxexcel_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_xxexcel_globals *xxexcel_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(xxexcel)
{

	zend_xxexcel_globals *xxexcel_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	xxexcel_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(xxexcel_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(xxexcel_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(xxexcel)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(xxexcel)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_XXEXCEL_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_XXEXCEL_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_XXEXCEL_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_XXEXCEL_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_XXEXCEL_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(xxexcel)
{
	php_zephir_init_globals(xxexcel_globals TSRMLS_CC);
	php_zephir_init_module_globals(xxexcel_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(xxexcel)
{

}


zend_function_entry php_xxexcel_functions[] = {
ZEND_FE_END

};

zend_module_entry xxexcel_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_XXEXCEL_EXTNAME,
	php_xxexcel_functions,
	PHP_MINIT(xxexcel),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(xxexcel),
#else
	NULL,
#endif
	PHP_RINIT(xxexcel),
	PHP_RSHUTDOWN(xxexcel),
	PHP_MINFO(xxexcel),
	PHP_XXEXCEL_VERSION,
	ZEND_MODULE_GLOBALS(xxexcel),
	PHP_GINIT(xxexcel),
	PHP_GSHUTDOWN(xxexcel),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_XXEXCEL
ZEND_GET_MODULE(xxexcel)
#endif
