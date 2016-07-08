
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/file.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/hash.h"


/**
 * a simple and fast excel writer
 */
ZEPHIR_INIT_CLASS(XxExcel_Writer) {

	ZEPHIR_REGISTER_CLASS(XxExcel, Writer, xxexcel, writer, xxexcel_writer_method_entry, 0);

	/**
	 * @var string
	 * The author for excel
	 */
	zend_declare_property_string(xxexcel_writer_ce, SL("author"), "XxExcel", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array
	 * The data of sheets
	 */
	zend_declare_property_null(xxexcel_writer_ce, SL("sheets"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 * The excel file to save to
	 */
	zend_declare_property_string(xxexcel_writer_ce, SL("fileName"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var int
	 * The sheets total
	 */
	zend_declare_property_long(xxexcel_writer_ce, SL("sheetsCount"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 * The template for worksheet
	 */
	zend_declare_property_string(xxexcel_writer_ce, SL("sheetTemplate"), "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\" mc:Ignorable=\"x14ac\" xmlns:x14ac=\"http://schemas.microsoft.com/office/spreadsheetml/2009/9/ac\"><dimension ref=\"A1:{$maxCell}\"/><sheetViews><sheetView tabSelected=\"{$tabSelected}\" zoomScaleNormal=\"100\" workbookViewId=\"0\"/></sheetViews><sheetFormatPr defaultRowHeight=\"13.8\" x14ac:dyDescent=\"0.25\"/><cols><col min=\"1\" max=\"1025\" width=\"15\"/></cols><sheetData>{$rows}</sheetData><phoneticPr fontId=\"1\" type=\"noConversion\"/><pageMargins left=\"0.5\" right=\"0.5\" top=\"1\" bottom=\"1\" header=\"0.5\" footer=\"0.5\"/><pageSetup paperSize=\"9\" orientation=\"portrait\" useFirstPageNumber=\"1\" r:id=\"rId1\"/><headerFooter><oddHeader>&amp;C&amp;\"Times New Roman,Regular\"&amp;12&amp;A</oddHeader><oddFooter>&amp;C&amp;\"Times New Roman,Regular\"&amp;12Page &amp;P</oddFooter></headerFooter></worksheet>", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 * The template for workbook
	 */
	zend_declare_property_string(xxexcel_writer_ce, SL("workbookTemplate"), "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\"><fileVersion appName=\"Calc\"/><workbookPr backupFile=\"false\" showObjects=\"all\" date1904=\"false\"/><workbookProtection/><bookViews><workbookView activeTab=\"0\" firstSheet=\"0\" showHorizontalScroll=\"true\" showSheetTabs=\"true\" showVerticalScroll=\"true\" tabRatio=\"212\" windowHeight=\"8192\" windowWidth=\"16384\" xWindow=\"0\" yWindow=\"0\"/></bookViews><sheets>{$sheets}</sheets><calcPr iterateCount=\"100\" refMode=\"A1\" iterate=\"false\" iterateDelta=\"0.001\"/></workbook>", ZEND_ACC_PROTECTED TSRMLS_CC);

	xxexcel_writer_ce->create_object = zephir_init_properties_XxExcel_Writer;
	/**
	 * @var int
	 * The Max Row
	 */
	zephir_declare_class_constant_long(xxexcel_writer_ce, SL("EXCEL_2007_MAX_ROW"), 1048576);

	/**
	 * @var int
	 * The Max Column
	 */
	zephir_declare_class_constant_long(xxexcel_writer_ce, SL("EXCEL_2007_MAX_COL"), 16384);

	return SUCCESS;

}

/**
 * The author for excel
 */
PHP_METHOD(XxExcel_Writer, setAuthor) {

	zval *author_param = NULL;
	zval author;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&author);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &author_param);

	zephir_get_strval(&author, author_param);


	zephir_update_property_zval(this_ptr, SL("author"), &author);
	ZEPHIR_MM_RESTORE();

}

/**
 * The author for excel
 */
PHP_METHOD(XxExcel_Writer, getAuthor) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "author");

}

/**
 * The data of sheets
 */
PHP_METHOD(XxExcel_Writer, setSheets) {

	zval *sheets_param = NULL;
	zval sheets;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&sheets);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sheets_param);

	zephir_get_arrval(&sheets, sheets_param);


	zephir_update_property_zval(this_ptr, SL("sheets"), &sheets);
	ZEPHIR_MM_RESTORE();

}

/**
 * The data of sheets
 */
PHP_METHOD(XxExcel_Writer, getSheets) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "sheets");

}

/**
 * The excel file to save to
 */
PHP_METHOD(XxExcel_Writer, setFileName) {

	zval *fileName_param = NULL;
	zval fileName;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&fileName);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &fileName_param);

	zephir_get_strval(&fileName, fileName_param);


	zephir_update_property_zval(this_ptr, SL("fileName"), &fileName);
	ZEPHIR_MM_RESTORE();

}

/**
 * The excel file to save to
 */
PHP_METHOD(XxExcel_Writer, getFileName) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "fileName");

}

/**
 * The sheets total
 */
PHP_METHOD(XxExcel_Writer, setSheetsCount) {

	zval *sheetsCount_param = NULL, _0;
	int sheetsCount;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &sheetsCount_param);

	sheetsCount = zephir_get_intval(sheetsCount_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, sheetsCount);
	zephir_update_property_zval(this_ptr, SL("sheetsCount"), &_0);

}

/**
 * The sheets total
 */
PHP_METHOD(XxExcel_Writer, getSheetsCount) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "sheetsCount");

}

/**
 * The template for workbook
 */
PHP_METHOD(XxExcel_Writer, setWorkbookTemplate) {

	zval *workbookTemplate_param = NULL;
	zval workbookTemplate;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&workbookTemplate);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &workbookTemplate_param);

	zephir_get_strval(&workbookTemplate, workbookTemplate_param);


	zephir_update_property_zval(this_ptr, SL("workbookTemplate"), &workbookTemplate);
	ZEPHIR_MM_RESTORE();

}

/**
 * The template for workbook
 */
PHP_METHOD(XxExcel_Writer, getWorkbookTemplate) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "workbookTemplate");

}

/**
 * @param string fileName
 * @return boolean
 */
PHP_METHOD(XxExcel_Writer, build) {

	zend_bool _10$$5;
	zephir_fcall_cache_entry *_1 = NULL, *_12 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, i;
	zval *fileName_param = NULL, _0, _8, _17, zip, status, _21, _25, _26, _27, _28, _29, _37, _38, _39, _40, _41, _2$$3, _3$$3, _4$$3, _5$$4, _6$$4, _7$$4, _dir$$5, _9$$5, _11$$5, _16$$5, _13$$6, _15$$6, _18$$7, _20$$7, _22$$8, _24$$8, _30$$9, _31$$9, _32$$9, _33$$9, _34$$9, _35$$9, _36$$9;
	zval fileName, _14$$6, _19$$7, _23$$8;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&fileName);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&zip);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_dir$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&_32$$9);
	ZVAL_UNDEF(&_33$$9);
	ZVAL_UNDEF(&_34$$9);
	ZVAL_UNDEF(&_35$$9);
	ZVAL_UNDEF(&_36$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &fileName_param);

	zephir_get_strval(&fileName, fileName_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getsheetscount", &_1, 0);
	zephir_check_call_status();
	if (ZEPHIR_LT_LONG(&_0, 1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "Empty sheets, can not build.");
		ZVAL_LONG(&_4$$3, 10001);
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 2, &_3$$3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "xxexcel/writer.zep", 65 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_IS_EMPTY(&fileName)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(&_6$$4);
		ZVAL_STRING(&_6$$4, "Empty fileName, can not build.");
		ZVAL_LONG(&_7$$4, 10002);
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 2, &_6$$4, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "xxexcel/writer.zep", 68 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_FUNCTION(&_8, "is_file", NULL, 3, &fileName);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_8)) {
		ZEPHIR_INIT_VAR(&_dir$$5);
		ZVAL_STRING(&_dir$$5, "");
		ZEPHIR_CALL_FUNCTION(&_dir$$5, "dirname", NULL, 4, &fileName);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_9$$5, "is_dir", NULL, 5, &_dir$$5);
		zephir_check_call_status();
		_10$$5 = ZEPHIR_IS_FALSE_IDENTICAL(&_9$$5);
		if (!(_10$$5)) {
			ZEPHIR_CALL_FUNCTION(&_11$$5, "is_writeable", &_12, 6, &_dir$$5);
			zephir_check_call_status();
			_10$$5 = ZEPHIR_IS_FALSE_IDENTICAL(&_11$$5);
		}
		if (_10$$5) {
			ZEPHIR_INIT_VAR(&_13$$6);
			object_init_ex(&_13$$6, zend_exception_get_default(TSRMLS_C));
			ZEPHIR_INIT_VAR(&_14$$6);
			ZEPHIR_CONCAT_VS(&_14$$6, &fileName, " not exist, and can not be created");
			ZVAL_LONG(&_15$$6, 20001);
			ZEPHIR_CALL_METHOD(NULL, &_13$$6, "__construct", NULL, 2, &_14$$6, &_15$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_13$$6, "xxexcel/writer.zep", 74 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_16$$5);
		ZVAL_STRING(&_16$$5, "");
		zephir_file_put_contents(NULL, &fileName, &_16$$5 TSRMLS_CC);
	}
	ZEPHIR_CALL_FUNCTION(&_17, "is_writeable", &_12, 6, &fileName);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_17)) {
		ZEPHIR_INIT_VAR(&_18$$7);
		object_init_ex(&_18$$7, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(&_19$$7);
		ZEPHIR_CONCAT_VS(&_19$$7, &fileName, " can not be wrote.");
		ZVAL_LONG(&_20$$7, 20002);
		ZEPHIR_CALL_METHOD(NULL, &_18$$7, "__construct", NULL, 2, &_19$$7, &_20$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_18$$7, "xxexcel/writer.zep", 79 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&zip);
	object_init_ex(&zip, zephir_get_internal_ce(SL("ziparchive")));
	if (zephir_has_constructor(&zip TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, &zip, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&status);
	ZVAL_BOOL(&status, 0);
	ZVAL_LONG(&_21, 1);
	ZEPHIR_CALL_METHOD(&status, &zip, "open", NULL, 0, &fileName, &_21);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&status)) {
		ZEPHIR_INIT_VAR(&_22$$8);
		object_init_ex(&_22$$8, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(&_23$$8);
		ZEPHIR_CONCAT_SV(&_23$$8, "Can not create zip file with filename:", &fileName);
		ZVAL_LONG(&_24$$8, 20003);
		ZEPHIR_CALL_METHOD(NULL, &_22$$8, "__construct", NULL, 2, &_23$$8, &_24$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_22$$8, "xxexcel/writer.zep", 86 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setfilename", NULL, 0, &fileName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_25);
	ZVAL_STRING(&_25, "docProps/");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addemptydir", NULL, 0, &_25);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_26, this_ptr, "buildappxml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "docProps/app.xml");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_26);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_27, this_ptr, "buildcorexml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "docProps/core.xml");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_27);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "_rels/");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addemptydir", NULL, 0, &_25);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_28, this_ptr, "buildrelationshipsxml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "_rels/.rels");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_28);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "xl/worksheets/");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addemptydir", NULL, 0, &_25);
	zephir_check_call_status();
	i = 0;
	while (1) {
		ZEPHIR_CALL_METHOD(&_29, this_ptr, "getsheetscount", &_1, 0);
		zephir_check_call_status();
		if (!(ZEPHIR_GT_LONG(&_29, i))) {
			break;
		}
		zephir_read_property(&_30$$9, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_31$$9, &_30$$9, i, PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 99 TSRMLS_CC);
		zephir_array_fetch_string(&_32$$9, &_31$$9, SL("xmlname"), PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 99 TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_33$$9);
		ZEPHIR_CONCAT_SV(&_33$$9, "xl/worksheets/", &_32$$9);
		zephir_read_property(&_34$$9, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_35$$9, &_34$$9, i, PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 99 TSRMLS_CC);
		zephir_array_fetch_string(&_36$$9, &_35$$9, SL("content"), PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 99 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_33$$9, &_36$$9);
		zephir_check_call_status();
		i = (i + 1);
	}
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "xl/sharedStrings.xml");
	ZEPHIR_INIT_VAR(&_37);
	ZVAL_STRING(&_37, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<sst count=\"0\" uniqueCount=\"0\" xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\"></sst>");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_37);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_38, this_ptr, "buildworkbookxml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "xl/workbook.xml");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_38);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_39, this_ptr, "buildstylesxml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "xl/styles.xml");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_39);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_40, this_ptr, "buildcontenttypesxml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "[Content_Types].xml");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_40);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "xl/_rels/");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addemptydir", NULL, 0, &_25);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_41, this_ptr, "buildworkbookrelsxml", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_25);
	ZVAL_STRING(&_25, "xl/_rels/workbook.xml.rels");
	ZEPHIR_CALL_METHOD(NULL, &zip, "addfromstring", NULL, 0, &_25, &_41);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &zip, "close", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildAppXML) {

	ZEPHIR_INIT_THIS();


	RETURN_STRING("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<Properties xmlns=\"http://schemas.openxmlformats.org/officeDocument/2006/extended-properties\" xmlns:vt=\"http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes\"><TotalTime>0</TotalTime></Properties>");

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildCoreXML) {

	zval time, _0, _1, _2;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&time);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&time);
	ZVAL_STRING(&time, "");
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Y-m-d\\TH:i:s.00\\Z");
	ZEPHIR_CALL_FUNCTION(&time, "date", NULL, 7, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getauthor", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "xmlspecialchars", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<cp:coreProperties xmlns:cp=\"http://schemas.openxmlformats.org/package/2006/metadata/core-properties\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcmitype=\"http://purl.org/dc/dcmitype/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><dc:creator>", &_1, "</dc:creator><cp:revision>0</cp:revision><dcterms:created xsi:type=\"dcterms:W3CDTF\">", &time, "</dcterms:created></cp:coreProperties>");
	RETURN_MM();

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildRelationshipsXML) {

	ZEPHIR_INIT_THIS();


	RETURN_STRING("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\"><Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\" Target=\"xl/workbook.xml\"/><Relationship Id=\"rId2\" Type=\"http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties\" Target=\"docProps/core.xml\"/><Relationship Id=\"rId3\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties\" Target=\"docProps/app.xml\"/>\n</Relationships>");

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildWorkbookXML) {

	zval xml, _sheets, _0, _12, _13, _2$$3, _3$$3, _4$$3, _5$$3, _7$$3, _8$$3, _10$$3, _11$$3;
	zephir_fcall_cache_entry *_1 = NULL, *_6 = NULL, *_9 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, i;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&xml);
	ZVAL_UNDEF(&_sheets);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&xml);
	ZVAL_STRING(&xml, "");
	ZEPHIR_CALL_METHOD(&xml, this_ptr, "getworkbooktemplate", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_sheets);
	ZVAL_STRING(&_sheets, "");
	i = 0;
	while (1) {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "getsheetscount", &_1, 0);
		zephir_check_call_status();
		if (!(ZEPHIR_GT_LONG(&_0, i))) {
			break;
		}
		zephir_read_property(&_3$$3, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_4$$3, &_3$$3, i, PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 147 TSRMLS_CC);
		zephir_array_fetch_string(&_5$$3, &_4$$3, SL("name"), PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 147 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "xmlspecialchars", &_6, 0, &_5$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_7$$3, (i + 1));
		ZEPHIR_CALL_FUNCTION(&_8$$3, "strval", &_9, 8, &_7$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_7$$3, (i + 2));
		ZEPHIR_CALL_FUNCTION(&_10$$3, "strval", &_9, 8, &_7$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_11$$3);
		ZEPHIR_CONCAT_VSVSVSVS(&_11$$3, &_sheets, "<sheet name=\"", &_2$$3, "\" sheetId=\"", &_8$$3, "\" state=\"visible\" r:id=\"rId", &_10$$3, "\"/>");
		ZEPHIR_CPY_WRT(&_sheets, &_11$$3);
		i = (i + 1);
	}
	ZEPHIR_INIT_VAR(&_12);
	ZEPHIR_INIT_VAR(&_13);
	ZVAL_STRING(&_13, "{$sheets}");
	zephir_fast_str_replace(&_12, &_13, &_sheets, &xml TSRMLS_CC);
	ZEPHIR_CPY_WRT(&xml, &_12);
	RETURN_CCTOR(xml);

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildStylesXML) {

	ZEPHIR_INIT_THIS();


	RETURN_STRING("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<styleSheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">\n<numFmts count=\"1\"><numFmt numFmtId=\"164\" formatCode=\"GENERAL\" /></numFmts><fonts count=\"4\"><font><name val=\"Arial\"/><charset val=\"1\"/><family val=\"2\"/><sz val=\"10\"/></font><font><name val=\"Arial\"/><family val=\"0\"/><sz val=\"10\"/></font><font><name val=\"Arial\"/><family val=\"0\"/><sz val=\"10\"/></font><font><name val=\"Arial\"/><family val=\"0\"/><sz val=\"10\"/></font></fonts><fills count=\"2\"><fill><patternFill patternType=\"none\"/></fill><fill><patternFill patternType=\"gray125\"/></fill></fills><borders count=\"1\"><border diagonalDown=\"false\" diagonalUp=\"false\"><left/><right/><top/><bottom/><diagonal/></border></borders><cellStyleXfs count=\"20\"><xf applyAlignment=\"true\" applyBorder=\"true\" applyFont=\"true\" applyProtection=\"true\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"164\"><alignment horizontal=\"general\" indent=\"0\" shrinkToFit=\"false\" textRotation=\"0\" vertical=\"bottom\" wrapText=\"false\"/><protection hidden=\"false\" locked=\"true\"/></xf><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"2\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"2\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"43\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"41\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"44\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"42\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"9\"/></cellStyleXfs><cellXfs count=\"1\"><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"false\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"164\" xfId=\"0\"/></cellXfs><cellStyles count=\"6\"><cellStyle builtinId=\"0\" customBuiltin=\"false\" name=\"Normal\" xfId=\"0\"/><cellStyle builtinId=\"3\" customBuiltin=\"false\" name=\"Comma\" xfId=\"15\"/><cellStyle builtinId=\"6\" customBuiltin=\"false\" name=\"Comma [0]\" xfId=\"16\"/><cellStyle builtinId=\"4\" customBuiltin=\"false\" name=\"Currency\" xfId=\"17\"/><cellStyle builtinId=\"7\" customBuiltin=\"false\" name=\"Currency [0]\" xfId=\"18\"/><cellStyle builtinId=\"5\" customBuiltin=\"false\" name=\"Percent\" xfId=\"19\"/></cellStyles>\n</styleSheet>");

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildWorkbookRelsXML) {

	zval _12;
	zval xml, _0, _8, _9, _10, _11, _2$$3, _3$$3, _5$$3, _6$$3, _7$$3;
	zephir_fcall_cache_entry *_1 = NULL, *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, i;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&xml);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_12);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&xml);
	ZVAL_STRING(&xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">\n<Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles\" Target=\"styles.xml\"/>");
	i = 0;
	while (1) {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "getsheetscount", &_1, 0);
		zephir_check_call_status();
		if (!(ZEPHIR_GT_LONG(&_0, i))) {
			break;
		}
		ZVAL_LONG(&_2$$3, (i + 2));
		ZEPHIR_CALL_FUNCTION(&_3$$3, "strval", &_4, 8, &_2$$3);
		zephir_check_call_status();
		zephir_read_property(&_2$$3, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_5$$3, &_2$$3, i, PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 168 TSRMLS_CC);
		zephir_array_fetch_string(&_6$$3, &_5$$3, SL("xmlname"), PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 168 TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_7$$3);
		ZEPHIR_CONCAT_VSVSVS(&_7$$3, &xml, "<Relationship Id=\"rId", &_3$$3, "\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\" Target=\"worksheets/", &_6$$3, "\"/>");
		ZEPHIR_CPY_WRT(&xml, &_7$$3);
		i = (i + 1);
	}
	ZEPHIR_CALL_METHOD(&_8, this_ptr, "getsheetscount", &_1, 0);
	zephir_check_call_status();
	ZVAL_LONG(&_9, (zephir_get_numberval(&_8) + 2));
	ZEPHIR_CALL_FUNCTION(&_10, "strval", &_4, 8, &_9);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_11);
	ZEPHIR_CONCAT_VSVS(&_11, &xml, "<Relationship Id=\"rId", &_10, "\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings\" Target=\"sharedStrings.xml\"/>\n</Relationships>");
	ZEPHIR_CPY_WRT(&xml, &_11);
	zephir_get_strval(&_12, &xml);
	RETURN_CTOR(_12);

}

/**
 * @return string
 */
PHP_METHOD(XxExcel_Writer, buildContentTypesXML) {

	zval _7;
	zval xml, _0, _6, _2$$3, _3$$3, _4$$3, _5$$3;
	zephir_fcall_cache_entry *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, i;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&xml);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&xml);
	ZVAL_STRING(&xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">\n<Override PartName=\"/_rels/.rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>\n<Override PartName=\"/xl/_rels/workbook.xml.rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>\n<Override PartName=\"/xl/workbook.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>");
	i = 0;
	while (1) {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "getsheetscount", &_1, 0);
		zephir_check_call_status();
		if (!(ZEPHIR_GT_LONG(&_0, i))) {
			break;
		}
		zephir_read_property(&_2$$3, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_3$$3, &_2$$3, i, PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 183 TSRMLS_CC);
		zephir_array_fetch_string(&_4$$3, &_3$$3, SL("xmlname"), PH_NOISY | PH_READONLY, "xxexcel/writer.zep", 183 TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &xml, "<Override PartName=\"/xl/worksheets/", &_4$$3, "\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>");
		ZEPHIR_CPY_WRT(&xml, &_5$$3);
		i = (i + 1);
	}
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_VS(&_6, &xml, "<Override PartName=\"/xl/sharedStrings.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sharedStrings+xml\"/>\n<Override PartName=\"/xl/styles.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>\n<Override PartName=\"/docProps/core.xml\" ContentType=\"application/vnd.openxmlformats-package.core-properties+xml\"/>\n<Override PartName=\"/docProps/app.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.extended-properties+xml\"/>\n</Types>");
	ZEPHIR_CPY_WRT(&xml, &_6);
	zephir_get_strval(&_7, &xml);
	RETURN_CTOR(_7);

}

/**
 * @param array data
 * @param string sheetName
 * @return boolean
 */
PHP_METHOD(XxExcel_Writer, addSheet) {

	zephir_fcall_cache_entry *_10 = NULL, *_16 = NULL, *_19 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, tabSelected, i, j, maxCellNumber;
	zval sheetName, content, _1, _rowStr, cellLabel, _cellStr, maxCell, _31, _17$$4;
	zval *data_param = NULL, *sheetName_param = NULL, _0, _2, _3, _4, _5, _6, row, cell, *_7, _24, _25, _26, _27, _28, _29, _30, _32, _33, _34, _35, _36, _8$$3, _9$$3, _11$$3, *_12$$3, _21$$3, _22$$3, _23$$3, _13$$4, _14$$4, _15$$4, _18$$4, _20$$4;
	zval data, rowStr, cellStr, sheet;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&rowStr);
	ZVAL_UNDEF(&cellStr);
	ZVAL_UNDEF(&sheet);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&cell);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_22$$3);
	ZVAL_UNDEF(&_23$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_18$$4);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&sheetName);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_rowStr);
	ZVAL_UNDEF(&cellLabel);
	ZVAL_UNDEF(&_cellStr);
	ZVAL_UNDEF(&maxCell);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_17$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &data_param, &sheetName_param);

	zephir_get_arrval(&data, data_param);
	if (!sheetName_param) {
		ZEPHIR_INIT_VAR(&sheetName);
		ZVAL_STRING(&sheetName, "Sheet1");
	} else {
		zephir_get_strval(&sheetName, sheetName_param);
	}


	ZEPHIR_INIT_VAR(&content);
	ZVAL_STRING(&content, "");
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("sheetTemplate"), PH_NOISY_CC);
	zephir_get_strval(&_1, &_0);
	ZEPHIR_CPY_WRT(&content, &_1);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getsheetscount", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(&_3, 0)) {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_LONG(&_2, 1);
	} else {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_LONG(&_2, 0);
	}
	tabSelected = zephir_get_numberval(&_2);
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "{$tabSelected}");
	ZVAL_LONG(&_6, tabSelected);
	zephir_fast_str_replace(&_4, &_5, &_6, &content TSRMLS_CC);
	zephir_get_strval(&content, &_4);
	i = 1;
	j = 0;
	ZEPHIR_INIT_VAR(&rowStr);
	array_init(&rowStr);
	ZEPHIR_INIT_VAR(&cellStr);
	array_init(&cellStr);
	ZEPHIR_INIT_VAR(&_rowStr);
	ZVAL_STRING(&_rowStr, "");
	ZEPHIR_INIT_VAR(&cellLabel);
	ZVAL_STRING(&cellLabel, "");
	ZEPHIR_INIT_VAR(&_cellStr);
	ZVAL_STRING(&_cellStr, "");
	maxCellNumber = 0;
	zephir_is_iterable(&data, 0, "xxexcel/writer.zep", 229);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&data), _7)
	{
		ZEPHIR_INIT_NVAR(&row);
		ZVAL_COPY(&row, _7);
		ZVAL_LONG(&_8$$3, i);
		ZEPHIR_CALL_FUNCTION(&_9$$3, "strval", &_10, 8, &_8$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_11$$3);
		ZEPHIR_CONCAT_SVS(&_11$$3, "<row collapsed=\"false\" customFormat=\"false\" customHeight=\"false\" hidden=\"false\" ht=\"12.1\" outlineLevel=\"0\" r=\"", &_9$$3, "\">");
		zephir_get_strval(&_rowStr, &_11$$3);
		j = 1;
		ZEPHIR_INIT_NVAR(&cellStr);
		array_init(&cellStr);
		zephir_is_iterable(&row, 0, "xxexcel/writer.zep", 225);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _12$$3)
		{
			ZEPHIR_INIT_NVAR(&cell);
			ZVAL_COPY(&cell, _12$$3);
			ZVAL_LONG(&_14$$4, (i - 1));
			ZVAL_LONG(&_15$$4, (j - 1));
			ZEPHIR_CALL_METHOD(&_13$$4, this_ptr, "getcellmark", &_16, 0, &_14$$4, &_15$$4);
			zephir_check_call_status();
			zephir_get_strval(&_17$$4, &_13$$4);
			ZEPHIR_CPY_WRT(&cellLabel, &_17$$4);
			ZEPHIR_CALL_METHOD(&_18$$4, this_ptr, "xmlspecialchars", &_19, 0, &cell);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_20$$4);
			ZEPHIR_CONCAT_SVSVS(&_20$$4, "<c r=\"", &cellLabel, "\" s=\"0\" t=\"inlineStr\"><is><t>", &_18$$4, "</t></is></c>");
			zephir_get_strval(&_cellStr, &_20$$4);
			zephir_array_append(&cellStr, &_cellStr, PH_SEPARATE, "xxexcel/writer.zep", 219);
			j = (j + 1);
			if (j > maxCellNumber) {
				maxCellNumber = j;
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&cell);
		ZEPHIR_INIT_NVAR(&_22$$3);
		zephir_fast_join_str(&_22$$3, SL(""), &cellStr TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_23$$3);
		ZEPHIR_CONCAT_VS(&_23$$3, &_22$$3, "</row>");
		zephir_concat_self(&_rowStr, &_23$$3 TSRMLS_CC);
		zephir_array_append(&rowStr, &_rowStr, PH_SEPARATE, "xxexcel/writer.zep", 226);
		i = (i + 1);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_VAR(&_24);
	ZEPHIR_INIT_VAR(&_26);
	zephir_fast_join_str(&_26, SL(""), &rowStr TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_27);
	ZVAL_STRING(&_27, "{$rows}");
	zephir_fast_str_replace(&_24, &_27, &_26, &content TSRMLS_CC);
	zephir_get_strval(&content, &_24);
	ZVAL_LONG(&_29, (zephir_fast_count_int(&data TSRMLS_CC) - 1));
	ZVAL_LONG(&_30, maxCellNumber);
	ZEPHIR_CALL_METHOD(&_28, this_ptr, "getcellmark", &_16, 0, &_29, &_30);
	zephir_check_call_status();
	zephir_get_strval(&_31, &_28);
	ZEPHIR_CPY_WRT(&maxCell, &_31);
	ZEPHIR_INIT_VAR(&_32);
	ZEPHIR_INIT_VAR(&_33);
	ZVAL_STRING(&_33, "{$maxCell}");
	zephir_fast_str_replace(&_32, &_33, &maxCell, &content TSRMLS_CC);
	zephir_get_strval(&content, &_32);
	ZEPHIR_INIT_VAR(&sheet);
	zephir_create_array(&sheet, 3, 0 TSRMLS_CC);
	zephir_array_update_string(&sheet, SL("name"), &sheetName, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_34, this_ptr, "getsheetscount", NULL, 0);
	zephir_check_call_status();
	ZVAL_LONG(&_29, (zephir_get_numberval(&_34) + 1));
	ZEPHIR_CALL_FUNCTION(&_35, "strval", &_10, 8, &_29);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_36);
	ZEPHIR_CONCAT_SVS(&_36, "sheet", &_35, ".xml");
	zephir_array_update_string(&sheet, SL("xmlname"), &_36, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sheet, SL("content"), &content, PH_COPY | PH_SEPARATE);
	zephir_update_property_array_append(this_ptr, SL("sheets"), &sheet TSRMLS_CC);
	zephir_read_property(&_29, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_30, zephir_fast_count_int(&_29 TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setsheetscount", NULL, 0, &_30);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);

}

/**
 * Encode string , so it could fit for excel
 * @param val string
 * @return string
 */
PHP_METHOD(XxExcel_Writer, xmlSpecialChars) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *val_param = NULL, _0, _1, _2, _3;
	zval val;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&val);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &val_param);

	zephir_get_strval(&val, val_param);


	ZEPHIR_CALL_FUNCTION(&_0, "htmlspecialchars", NULL, 9, &val);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "'");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "&#39;");
	ZEPHIR_INIT_VAR(&_3);
	zephir_fast_str_replace(&_3, &_1, &_2, &_0 TSRMLS_CC);
	RETURN_CCTOR(_3);

}

/**
 * convert row number and column number to column label A1-ZZ.
 * @param int rowNumber
 * @param int columnNumber
 * @return string
 */
PHP_METHOD(XxExcel_Writer, getCellMark) {

	zval r;
	zephir_fcall_cache_entry *_2 = NULL;
	zval *rowNumber_param = NULL, *columnNumber_param = NULL, _4, _5, _0$$3, _1$$3, _3$$3;
	int rowNumber, columnNumber, ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&r);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &rowNumber_param, &columnNumber_param);

	rowNumber = zephir_get_intval(rowNumber_param);
	columnNumber = zephir_get_intval(columnNumber_param);


	ZEPHIR_INIT_VAR(&r);
	ZVAL_STRING(&r, "");
	while (1) {
		if (!(columnNumber >= 0)) {
			break;
		}
		ZVAL_DOUBLE(&_0$$3, (zephir_safe_mod_long_long(columnNumber, 26 TSRMLS_CC) + (double) (0x41)));
		ZEPHIR_CALL_FUNCTION(&_1$$3, "chr", &_2, 10, &_0$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_3$$3);
		ZEPHIR_CONCAT_VV(&_3$$3, &_1$$3, &r);
		zephir_get_strval(&r, &_3$$3);
		ZVAL_DOUBLE(&_0$$3, zephir_safe_div_long_long(columnNumber, 26 TSRMLS_CC));
		columnNumber = (zephir_get_intval(&_0$$3) - 1);
	}
	ZVAL_LONG(&_4, (rowNumber + 1));
	ZEPHIR_CALL_FUNCTION(&_5, "strval", NULL, 8, &_4);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &r, &_5);
	RETURN_MM();

}

zend_object *zephir_init_properties_XxExcel_Writer(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("sheets"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("sheets"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

