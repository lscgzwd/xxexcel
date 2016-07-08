
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/concat.h"


/**
 * Class Reader excel2007 解析类
 * @package XxExcel
 */
ZEPHIR_INIT_CLASS(XxExcel_Reader) {

	ZEPHIR_REGISTER_CLASS(XxExcel, Reader, xxexcel, reader, xxexcel_reader_method_entry, 0);

	/**
	 * @var \ZipArchive
	 */
	zend_declare_property_null(xxexcel_reader_ce, SL("zip"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(xxexcel_reader_ce, SL("currentSheet"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xxexcel_reader_ce, SL("sheetInfos"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xxexcel_reader_ce, SL("sharedStrings"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xxexcel_reader_ce, SL("sheetDatas"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(xxexcel_reader_ce, SL("maxRow"), 5000, ZEND_ACC_PROTECTED TSRMLS_CC);

	xxexcel_reader_ce->create_object = zephir_init_properties_XxExcel_Reader;
	return SUCCESS;

}

PHP_METHOD(XxExcel_Reader, setCurrentSheet) {

	zval *currentSheet, currentSheet_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&currentSheet_sub);

	zephir_fetch_params(0, 1, 0, &currentSheet);



	zephir_update_property_zval(this_ptr, SL("currentSheet"), currentSheet);

}

PHP_METHOD(XxExcel_Reader, getCurrentSheet) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "currentSheet");

}

PHP_METHOD(XxExcel_Reader, setSheetInfos) {

	zval *sheetInfos, sheetInfos_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&sheetInfos_sub);

	zephir_fetch_params(0, 1, 0, &sheetInfos);



	zephir_update_property_zval(this_ptr, SL("sheetInfos"), sheetInfos);

}

PHP_METHOD(XxExcel_Reader, getSheetInfos) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "sheetInfos");

}

PHP_METHOD(XxExcel_Reader, setSharedStrings) {

	zval *sharedStrings, sharedStrings_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&sharedStrings_sub);

	zephir_fetch_params(0, 1, 0, &sharedStrings);



	zephir_update_property_zval(this_ptr, SL("sharedStrings"), sharedStrings);

}

PHP_METHOD(XxExcel_Reader, getSharedStrings) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "sharedStrings");

}

PHP_METHOD(XxExcel_Reader, setSheetDatas) {

	zval *sheetDatas, sheetDatas_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&sheetDatas_sub);

	zephir_fetch_params(0, 1, 0, &sheetDatas);



	zephir_update_property_zval(this_ptr, SL("sheetDatas"), sheetDatas);

}

PHP_METHOD(XxExcel_Reader, getSheetDatas) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "sheetDatas");

}

PHP_METHOD(XxExcel_Reader, setMaxRow) {

	zval *maxRow, maxRow_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&maxRow_sub);

	zephir_fetch_params(0, 1, 0, &maxRow);



	zephir_update_property_zval(this_ptr, SL("maxRow"), maxRow);

}

PHP_METHOD(XxExcel_Reader, getMaxRow) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "maxRow");

}

/**
 * read an excel2007 file
 * @param string filename
 * @param string type
 * @return boolean
 */
PHP_METHOD(XxExcel_Reader, open) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *filename_param = NULL, *type_param = NULL, _zip;
	zval filename, type;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&filename);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&_zip);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &filename_param, &type_param);

	zephir_get_strval(&filename, filename_param);
	if (!type_param) {
		ZEPHIR_INIT_VAR(&type);
		ZVAL_STRING(&type, "Excel2007");
	} else {
		zephir_get_strval(&type, type_param);
	}


	ZEPHIR_INIT_VAR(&_zip);
	object_init_ex(&_zip, zephir_get_internal_ce(SL("ziparchive")));
	if (zephir_has_constructor(&_zip TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, &_zip, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, &_zip, "open", NULL, 0, &filename);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("zip"), &_zip);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "readsharedstring", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);

}

PHP_METHOD(XxExcel_Reader, readSharedString) {

	zend_bool _5$$3;
	zval xml, _xmlString, _0, _1, _2, _4$$3, _6$$3, _7$$4;
	zephir_fcall_cache_entry *_3 = NULL, *_8 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&xml);
	ZVAL_UNDEF(&_xmlString);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&xml);
	object_init_ex(&xml, zephir_get_internal_ce(SL("xmlreader")));
	if (zephir_has_constructor(&xml TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, &xml, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_property(&_0, this_ptr, SL("zip"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "xl/sharedStrings.xml");
	ZEPHIR_CALL_METHOD(&_xmlString, &_0, "getfromname", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &xml, "xml", NULL, 0, &_xmlString);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_CALL_METHOD(&_2, &xml, "read", &_3, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_2))) {
			break;
		}
		zephir_read_property(&_4$$3, &xml, SL("name"), PH_NOISY_CC | PH_READONLY);
		_5$$3 = ZEPHIR_IS_STRING(&_4$$3, "t");
		if (_5$$3) {
			zephir_read_property(&_6$$3, &xml, SL("nodeType"), PH_NOISY_CC | PH_READONLY);
			_5$$3 = ZEPHIR_IS_LONG(&_6$$3, 1);
		}
		if (_5$$3) {
			ZEPHIR_CALL_METHOD(&_7$$4, &xml, "readstring", &_8, 0);
			zephir_check_call_status();
			zephir_update_property_array_append(this_ptr, SL("sharedStrings"), &_7$$4 TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(XxExcel_Reader, getSheetDataByIndex) {

	zend_bool _14$$4;
	zval rows, sharedStrings, _10, _rowIndexCache;
	zval sheetFile, nodeName, attrNameR, attrNameT, regx, blank;
	zephir_fcall_cache_entry *_12 = NULL, *_16 = NULL, *_17 = NULL, *_18 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, j;
	zval *index, index_sub, _0, _1, _5, _6, xml, _7, _8, _9, t, value, cr, _rowIndex, maxRow, _11, _20, _2$$3, _3$$3, _4$$3, _13$$4, _15$$4, _19$$10;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&xml);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&cr);
	ZVAL_UNDEF(&_rowIndex);
	ZVAL_UNDEF(&maxRow);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&sheetFile);
	ZVAL_UNDEF(&nodeName);
	ZVAL_UNDEF(&attrNameR);
	ZVAL_UNDEF(&attrNameT);
	ZVAL_UNDEF(&regx);
	ZVAL_UNDEF(&blank);
	ZVAL_UNDEF(&rows);
	ZVAL_UNDEF(&sharedStrings);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_rowIndexCache);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcurrentsheet", NULL, 0, index);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("sheetDatas"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("currentSheet"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_0, &_1)) {
		zephir_read_property(&_2$$3, this_ptr, SL("sheetDatas"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_4$$3);
		zephir_read_property(&_4$$3, this_ptr, SL("currentSheet"), PH_NOISY_CC);
		zephir_array_fetch(&_3$$3, &_2$$3, &_4$$3, PH_NOISY | PH_READONLY, "xxexcel/reader.zep", 60 TSRMLS_CC);
		RETURN_CTOR(_3$$3);
	}
	zephir_read_property(&_5, this_ptr, SL("currentSheet"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SVS(&_6, "xl/worksheets/sheet", &_5, ".xml");
	zephir_get_strval(&sheetFile, &_6);
	ZEPHIR_INIT_VAR(&xml);
	object_init_ex(&xml, zephir_get_internal_ce(SL("xmlreader")));
	if (zephir_has_constructor(&xml TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, &xml, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_property(&_7, this_ptr, SL("zip"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_8, &_7, "getfromname", NULL, 0, &sheetFile);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &xml, "xml", NULL, 0, &_8);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&rows);
	array_init(&rows);
	ZEPHIR_CALL_METHOD(&_9, this_ptr, "getsharedstrings", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_10, &_9);
	ZEPHIR_CPY_WRT(&sharedStrings, &_10);
	j = 0;
	ZEPHIR_INIT_VAR(&value);
	ZVAL_STRING(&value, "");
	ZEPHIR_INIT_VAR(&_rowIndexCache);
	array_init(&_rowIndexCache);
	ZEPHIR_INIT_VAR(&_rowIndex);
	ZVAL_LONG(&_rowIndex, 0);
	ZEPHIR_CALL_METHOD(&maxRow, this_ptr, "getmaxrow", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&nodeName);
	ZVAL_STRING(&nodeName, "c");
	ZEPHIR_INIT_VAR(&attrNameR);
	ZVAL_STRING(&attrNameR, "r");
	ZEPHIR_INIT_VAR(&attrNameT);
	ZVAL_STRING(&attrNameT, "t");
	ZEPHIR_INIT_VAR(&regx);
	ZVAL_STRING(&regx, "/\\D*/");
	ZEPHIR_INIT_VAR(&blank);
	ZVAL_STRING(&blank, "");
	while (1) {
		ZEPHIR_CALL_METHOD(&_11, &xml, "read", &_12, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_11))) {
			break;
		}
		zephir_read_property(&_13$$4, &xml, SL("name"), PH_NOISY_CC | PH_READONLY);
		_14$$4 = ZEPHIR_IS_EQUAL(&_13$$4, &nodeName);
		if (_14$$4) {
			zephir_read_property(&_15$$4, &xml, SL("nodeType"), PH_NOISY_CC | PH_READONLY);
			_14$$4 = ZEPHIR_IS_LONG(&_15$$4, 1);
		}
		if (_14$$4) {
			ZEPHIR_CALL_METHOD(&cr, &xml, "getattribute", &_16, 0, &attrNameR);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&t, &xml, "getattribute", &_16, 0, &attrNameT);
			zephir_check_call_status();
			if (zephir_array_isset(&_rowIndexCache, &cr)) {
				ZEPHIR_OBS_NVAR(&_rowIndex);
				zephir_array_fetch(&_rowIndex, &_rowIndexCache, &cr, PH_NOISY, "xxexcel/reader.zep", 86 TSRMLS_CC);
			} else {
				ZEPHIR_CALL_FUNCTION(&_rowIndex, "preg_replace", &_17, 1, &regx, &blank, &cr);
				zephir_check_call_status();
				zephir_array_update_zval(&_rowIndexCache, &cr, &_rowIndex, PH_COPY | PH_SEPARATE);
			}
			if (ZEPHIR_GT(&_rowIndex, &maxRow)) {
				continue;
			}
			if (ZEPHIR_IS_EMPTY(&t)) {
				ZEPHIR_INIT_NVAR(&t);
				ZVAL_STRING(&t, "s");
			}
			ZEPHIR_CALL_METHOD(&value, &xml, "readstring", &_18, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_STRING(&t, "s")) {
				zephir_array_fetch(&_19$$10, &sharedStrings, &value, PH_NOISY | PH_READONLY, "xxexcel/reader.zep", 99 TSRMLS_CC);
				ZEPHIR_CPY_WRT(&value, &_19$$10);
			}
			zephir_array_update_multi(&rows, &value TSRMLS_CC, SL("zz"), 2, &_rowIndex, &cr);
			j = (j + 1);
		}
	}
	ZEPHIR_OBS_VAR(&_20);
	zephir_read_property(&_20, this_ptr, SL("currentSheet"), PH_NOISY_CC);
	zephir_update_property_array(this_ptr, SL("sheetDatas"), &_20, &rows TSRMLS_CC);
	RETURN_CTOR(rows);

}

/**
 * @param int    rowIndex
 * @param string cell
 * @return mixed
 */
PHP_METHOD(XxExcel_Reader, getCellValueByRowAndColumn) {

	zval cell, _6;
	zval *rowIndex_param = NULL, *cell_param = NULL, _0, _1, _2, _3, _4, _5;
	int rowIndex;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&cell);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &rowIndex_param, &cell_param);

	if (!rowIndex_param) {
		rowIndex = 1;
	} else {
		rowIndex = zephir_get_intval(rowIndex_param);
	}
	if (!cell_param) {
		ZEPHIR_INIT_VAR(&cell);
		ZVAL_STRING(&cell, "A");
	} else {
		zephir_get_strval(&cell, cell_param);
	}


	zephir_read_property(&_0, this_ptr, SL("sheetDatas"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_VAR(&_2);
	zephir_read_property(&_2, this_ptr, SL("currentSheet"), PH_NOISY_CC);
	zephir_array_fetch(&_1, &_0, &_2, PH_NOISY | PH_READONLY, "xxexcel/reader.zep", 116 TSRMLS_CC);
	zephir_array_fetch_long(&_3, &_1, (rowIndex - 1), PH_NOISY | PH_READONLY, "xxexcel/reader.zep", 116 TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_LONG(&_5, rowIndex);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_VV(&_6, &cell, &_5);
	zephir_array_fetch(&_4, &_3, &_6, PH_NOISY | PH_READONLY, "xxexcel/reader.zep", 116 TSRMLS_CC);
	RETURN_CTOR(_4);

}

zend_object *zephir_init_properties_XxExcel_Reader(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _1$$3, _3$$4, _5$$5;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("sheetDatas"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("sheetDatas"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("sharedStrings"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("sharedStrings"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("sheetInfos"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("sheetInfos"), &_5$$5);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

