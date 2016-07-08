
extern zend_class_entry *xxexcel_reader_ce;

ZEPHIR_INIT_CLASS(XxExcel_Reader);

PHP_METHOD(XxExcel_Reader, setCurrentSheet);
PHP_METHOD(XxExcel_Reader, getCurrentSheet);
PHP_METHOD(XxExcel_Reader, setSheetInfos);
PHP_METHOD(XxExcel_Reader, getSheetInfos);
PHP_METHOD(XxExcel_Reader, setSharedStrings);
PHP_METHOD(XxExcel_Reader, getSharedStrings);
PHP_METHOD(XxExcel_Reader, setSheetDatas);
PHP_METHOD(XxExcel_Reader, getSheetDatas);
PHP_METHOD(XxExcel_Reader, setMaxRow);
PHP_METHOD(XxExcel_Reader, getMaxRow);
PHP_METHOD(XxExcel_Reader, open);
PHP_METHOD(XxExcel_Reader, readSharedString);
PHP_METHOD(XxExcel_Reader, getSheetDataByIndex);
PHP_METHOD(XxExcel_Reader, getCellValueByRowAndColumn);
zend_object *zephir_init_properties_XxExcel_Reader(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_setcurrentsheet, 0, 0, 1)
	ZEND_ARG_INFO(0, currentSheet)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_setsheetinfos, 0, 0, 1)
	ZEND_ARG_INFO(0, sheetInfos)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_setsharedstrings, 0, 0, 1)
	ZEND_ARG_INFO(0, sharedStrings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_setsheetdatas, 0, 0, 1)
	ZEND_ARG_INFO(0, sheetDatas)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_setmaxrow, 0, 0, 1)
	ZEND_ARG_INFO(0, maxRow)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_open, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_getsheetdatabyindex, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_reader_getcellvaluebyrowandcolumn, 0, 0, 0)
	ZEND_ARG_INFO(0, rowIndex)
	ZEND_ARG_INFO(0, cell)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xxexcel_reader_method_entry) {
	PHP_ME(XxExcel_Reader, setCurrentSheet, arginfo_xxexcel_reader_setcurrentsheet, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, getCurrentSheet, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, setSheetInfos, arginfo_xxexcel_reader_setsheetinfos, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, getSheetInfos, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, setSharedStrings, arginfo_xxexcel_reader_setsharedstrings, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, getSharedStrings, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, setSheetDatas, arginfo_xxexcel_reader_setsheetdatas, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, getSheetDatas, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, setMaxRow, arginfo_xxexcel_reader_setmaxrow, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, getMaxRow, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, open, arginfo_xxexcel_reader_open, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, readSharedString, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Reader, getSheetDataByIndex, arginfo_xxexcel_reader_getsheetdatabyindex, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Reader, getCellValueByRowAndColumn, arginfo_xxexcel_reader_getcellvaluebyrowandcolumn, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
