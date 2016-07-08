
extern zend_class_entry *xxexcel_writer_ce;

ZEPHIR_INIT_CLASS(XxExcel_Writer);

PHP_METHOD(XxExcel_Writer, setAuthor);
PHP_METHOD(XxExcel_Writer, getAuthor);
PHP_METHOD(XxExcel_Writer, setSheets);
PHP_METHOD(XxExcel_Writer, getSheets);
PHP_METHOD(XxExcel_Writer, setFileName);
PHP_METHOD(XxExcel_Writer, getFileName);
PHP_METHOD(XxExcel_Writer, setSheetsCount);
PHP_METHOD(XxExcel_Writer, getSheetsCount);
PHP_METHOD(XxExcel_Writer, setWorkbookTemplate);
PHP_METHOD(XxExcel_Writer, getWorkbookTemplate);
PHP_METHOD(XxExcel_Writer, build);
PHP_METHOD(XxExcel_Writer, buildAppXML);
PHP_METHOD(XxExcel_Writer, buildCoreXML);
PHP_METHOD(XxExcel_Writer, buildRelationshipsXML);
PHP_METHOD(XxExcel_Writer, buildWorkbookXML);
PHP_METHOD(XxExcel_Writer, buildStylesXML);
PHP_METHOD(XxExcel_Writer, buildWorkbookRelsXML);
PHP_METHOD(XxExcel_Writer, buildContentTypesXML);
PHP_METHOD(XxExcel_Writer, addSheet);
PHP_METHOD(XxExcel_Writer, xmlSpecialChars);
PHP_METHOD(XxExcel_Writer, getCellMark);
zend_object *zephir_init_properties_XxExcel_Writer(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_setauthor, 0, 0, 1)
	ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_setsheets, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, sheets, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_setfilename, 0, 0, 1)
	ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_setsheetscount, 0, 0, 1)
	ZEND_ARG_INFO(0, sheetsCount)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_setworkbooktemplate, 0, 0, 1)
	ZEND_ARG_INFO(0, workbookTemplate)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_build, 0, 0, 1)
	ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_addsheet, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
	ZEND_ARG_INFO(0, sheetName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_xmlspecialchars, 0, 0, 1)
	ZEND_ARG_INFO(0, val)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxexcel_writer_getcellmark, 0, 0, 2)
	ZEND_ARG_INFO(0, rowNumber)
	ZEND_ARG_INFO(0, columnNumber)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xxexcel_writer_method_entry) {
	PHP_ME(XxExcel_Writer, setAuthor, arginfo_xxexcel_writer_setauthor, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, getAuthor, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, setSheets, arginfo_xxexcel_writer_setsheets, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, getSheets, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, setFileName, arginfo_xxexcel_writer_setfilename, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, getFileName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, setSheetsCount, arginfo_xxexcel_writer_setsheetscount, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, getSheetsCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, setWorkbookTemplate, arginfo_xxexcel_writer_setworkbooktemplate, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, getWorkbookTemplate, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, build, arginfo_xxexcel_writer_build, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, buildAppXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, buildCoreXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, buildRelationshipsXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, buildWorkbookXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, buildStylesXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, buildWorkbookRelsXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, buildContentTypesXML, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, addSheet, arginfo_xxexcel_writer_addsheet, ZEND_ACC_PUBLIC)
	PHP_ME(XxExcel_Writer, xmlSpecialChars, arginfo_xxexcel_writer_xmlspecialchars, ZEND_ACC_PROTECTED)
	PHP_ME(XxExcel_Writer, getCellMark, arginfo_xxexcel_writer_getcellmark, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
