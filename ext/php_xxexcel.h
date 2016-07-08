
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_XXEXCEL_H
#define PHP_XXEXCEL_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_XXEXCEL_NAME        "XxExcel"
#define PHP_XXEXCEL_VERSION     "0.0.1"
#define PHP_XXEXCEL_EXTNAME     "xxexcel"
#define PHP_XXEXCEL_AUTHOR      "lushuncheng"
#define PHP_XXEXCEL_ZEPVERSION  "0.9.3a-dev-2fba6d7a44"
#define PHP_XXEXCEL_DESCRIPTION "XxExcel is a php extension to parse or create xlsx files"



ZEND_BEGIN_MODULE_GLOBALS(xxexcel)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(xxexcel)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(xxexcel)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(xxexcel, v)
#else
	#define ZEPHIR_GLOBAL(v) (xxexcel_globals.v)
#endif

#ifdef ZTS
	void ***tsrm_ls;
	#define ZEPHIR_VGLOBAL ((zend_xxexcel_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(xxexcel_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(xxexcel_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def xxexcel_globals
#define zend_zephir_globals_def zend_xxexcel_globals

extern zend_module_entry xxexcel_module_entry;
#define phpext_xxexcel_ptr &xxexcel_module_entry

#endif
