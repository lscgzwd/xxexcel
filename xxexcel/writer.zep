namespace XxExcel;
/**
 * a simple and fast excel writer
 */
class Writer
{
    /**
     * @var int
     * The Max Row
     */
    const EXCEL_2007_MAX_ROW = 1048576;
    /**
     * @var int
     * The Max Column
     */
    const EXCEL_2007_MAX_COL = 16384;

    /**
     * @var string
     * The author for excel
     */
    protected author        = "XxExcel" {
        set, get
    };
    /**
     * @var array
     * The data of sheets
     */
    protected sheets        = [] {
        set, get
    };
    /**
     * @var string
     * The excel file to save to
     */
    protected fileName      = "" {
        set, get
    };
    /**
     * @var int
     * The sheets total
     */
    protected sheetsCount = 0 {
        set, get
    };
    /**
     * @var string
     * The template for worksheet
     */
    protected sheetTemplate = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\" mc:Ignorable=\"x14ac\" xmlns:x14ac=\"http://schemas.microsoft.com/office/spreadsheetml/2009/9/ac\"><dimension ref=\"A1:{$maxCell}\"/><sheetViews><sheetView tabSelected=\"{$tabSelected}\" zoomScaleNormal=\"100\" workbookViewId=\"0\"/></sheetViews><sheetFormatPr defaultRowHeight=\"13.8\" x14ac:dyDescent=\"0.25\"/><cols><col min=\"1\" max=\"1025\" width=\"15\"/></cols><sheetData>{$rows}</sheetData><phoneticPr fontId=\"1\" type=\"noConversion\"/><pageMargins left=\"0.5\" right=\"0.5\" top=\"1\" bottom=\"1\" header=\"0.5\" footer=\"0.5\"/><pageSetup paperSize=\"9\" orientation=\"portrait\" useFirstPageNumber=\"1\" r:id=\"rId1\"/><headerFooter><oddHeader>&amp;C&amp;\"Times New Roman,Regular\"&amp;12&amp;A</oddHeader><oddFooter>&amp;C&amp;\"Times New Roman,Regular\"&amp;12Page &amp;P</oddFooter></headerFooter></worksheet>";
    /**
     * @var string
     * The template for workbook
     */
    protected workbookTemplate = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\"><fileVersion appName=\"Calc\"/><workbookPr backupFile=\"false\" showObjects=\"all\" date1904=\"false\"/><workbookProtection/><bookViews><workbookView activeTab=\"0\" firstSheet=\"0\" showHorizontalScroll=\"true\" showSheetTabs=\"true\" showVerticalScroll=\"true\" tabRatio=\"212\" windowHeight=\"8192\" windowWidth=\"16384\" xWindow=\"0\" yWindow=\"0\"/></bookViews><sheets>{$sheets}</sheets><calcPr iterateCount=\"100\" refMode=\"A1\" iterate=\"false\" iterateDelta=\"0.001\"/></workbook>" {
        set, get
    };
    /**
     * @param string fileName
     * @return boolean
     */
    public function build(string fileName) -> boolean
    {
        if this->getSheetsCount() < 1 {
            throw new \Exception("Empty sheets, can not build.", 10001);
        }
        if empty(fileName) {
            throw new \Exception("Empty fileName, can not build.", 10002);
        }
        if is_file(fileName) === false {
            var _dir = "";
            let _dir = dirname(fileName);
            if is_dir(_dir) === false || is_writeable(_dir) === false {
                throw new \Exception(fileName . " not exist, and can not be created", 20001);
            }
            file_put_contents(fileName, "");
        }
        if (is_writeable(fileName) === false) {
            throw new \Exception(fileName . " can not be wrote.", 20002);
        }
        var zip;
        let zip = new \ZipArchive();
        var status = false;
        let status = zip->open(fileName, \ZipArchive::CREATE);
        if (status === false) {
            throw new \Exception("Can not create zip file with filename:" . fileName, 20003);
        }
        this->setFileName(fileName);
        zip->addEmptyDir("docProps/");
        zip->addFromString("docProps/app.xml", this->buildAppXML());
        zip->addFromString("docProps/core.xml", $this->buildCoreXML());

        zip->addEmptyDir("_rels/");
        zip->addFromString("_rels/.rels", $this->buildRelationshipsXML());

        zip->addEmptyDir("xl/worksheets/");
        int i = 0;
        while i < this->getSheetsCount() {
            zip->addFromString("xl/worksheets/" . this->sheets[i]["xmlname"], this->sheets[i]["content"]);
            let i = i + 1;
        }
        zip->addFromString("xl/sharedStrings.xml", "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<sst count=\"0\" uniqueCount=\"0\" xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\"></sst>");
        zip->addFromString("xl/workbook.xml", this->buildWorkbookXML());
        zip->addFromString("xl/styles.xml", this->buildStylesXML());
        zip->addFromString("[Content_Types].xml", this->buildContentTypesXML());

        zip->addEmptyDir("xl/_rels/");
        zip->addFromString("xl/_rels/workbook.xml.rels", this->buildWorkbookRelsXML());
        zip->close();
        return true;
    }
    /**
     * @return string
     */
    protected function buildAppXML() -> string
    {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<Properties xmlns=\"http://schemas.openxmlformats.org/officeDocument/2006/extended-properties\" xmlns:vt=\"http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes\"><TotalTime>0</TotalTime></Properties>";
    }

    /**
     * @return string
     */
    protected function buildCoreXML() -> string
    {
        var time = "";
        let time = date("Y-m-d\\TH:i:s.00\\Z");
        return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<cp:coreProperties xmlns:cp=\"http://schemas.openxmlformats.org/package/2006/metadata/core-properties\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcmitype=\"http://purl.org/dc/dcmitype/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><dc:creator>" . this->xmlSpecialChars(this->getAuthor()) . "</dc:creator><cp:revision>0</cp:revision><dcterms:created xsi:type=\"dcterms:W3CDTF\">" . time . "</dcterms:created></cp:coreProperties>";
    }
    /**
     * @return string
     */
    protected function buildRelationshipsXML() -> string
    {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\"><Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\" Target=\"xl/workbook.xml\"/><Relationship Id=\"rId2\" Type=\"http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties\" Target=\"docProps/core.xml\"/><Relationship Id=\"rId3\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties\" Target=\"docProps/app.xml\"/>\n</Relationships>";
    }

    /**
     * @return string
     */
    protected function buildWorkbookXML() -> string
    {
        var xml = "";
        let xml = this->getWorkbookTemplate();
        var _sheets = "";
        int i = 0;
        while i < this->getSheetsCount() {
            let _sheets = _sheets . "<sheet name=\"" . this->xmlSpecialChars(this->sheets[i]["name"]) . "\" sheetId=\"" . strval(i + 1) . "\" state=\"visible\" r:id=\"rId" . strval(i + 2) . "\"/>";
            let i = i + 1;
        }
        let xml = str_replace("{$sheets}", _sheets, xml);
        return xml;
    }
    /**
     * @return string
     */
    protected function buildStylesXML() -> string
    {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<styleSheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">\n<numFmts count=\"1\"><numFmt numFmtId=\"164\" formatCode=\"GENERAL\" /></numFmts><fonts count=\"4\"><font><name val=\"Arial\"/><charset val=\"1\"/><family val=\"2\"/><sz val=\"10\"/></font><font><name val=\"Arial\"/><family val=\"0\"/><sz val=\"10\"/></font><font><name val=\"Arial\"/><family val=\"0\"/><sz val=\"10\"/></font><font><name val=\"Arial\"/><family val=\"0\"/><sz val=\"10\"/></font></fonts><fills count=\"2\"><fill><patternFill patternType=\"none\"/></fill><fill><patternFill patternType=\"gray125\"/></fill></fills><borders count=\"1\"><border diagonalDown=\"false\" diagonalUp=\"false\"><left/><right/><top/><bottom/><diagonal/></border></borders><cellStyleXfs count=\"20\"><xf applyAlignment=\"true\" applyBorder=\"true\" applyFont=\"true\" applyProtection=\"true\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"164\"><alignment horizontal=\"general\" indent=\"0\" shrinkToFit=\"false\" textRotation=\"0\" vertical=\"bottom\" wrapText=\"false\"/><protection hidden=\"false\" locked=\"true\"/></xf><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"2\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"2\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"0\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"43\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"41\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"44\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"42\"/><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"true\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"1\" numFmtId=\"9\"/></cellStyleXfs><cellXfs count=\"1\"><xf applyAlignment=\"false\" applyBorder=\"false\" applyFont=\"false\" applyProtection=\"false\" borderId=\"0\" fillId=\"0\" fontId=\"0\" numFmtId=\"164\" xfId=\"0\"/></cellXfs><cellStyles count=\"6\"><cellStyle builtinId=\"0\" customBuiltin=\"false\" name=\"Normal\" xfId=\"0\"/><cellStyle builtinId=\"3\" customBuiltin=\"false\" name=\"Comma\" xfId=\"15\"/><cellStyle builtinId=\"6\" customBuiltin=\"false\" name=\"Comma [0]\" xfId=\"16\"/><cellStyle builtinId=\"4\" customBuiltin=\"false\" name=\"Currency\" xfId=\"17\"/><cellStyle builtinId=\"7\" customBuiltin=\"false\" name=\"Currency [0]\" xfId=\"18\"/><cellStyle builtinId=\"5\" customBuiltin=\"false\" name=\"Percent\" xfId=\"19\"/></cellStyles>\n</styleSheet>";
    }
    /**
     * @return string
     */
    protected function buildWorkbookRelsXML() -> string
    {
        var xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">\n<Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles\" Target=\"styles.xml\"/>";
        int i = 0;
        while i < this->getSheetsCount() {
            let xml = xml . "<Relationship Id=\"rId" . strval(i + 2) . "\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\" Target=\"worksheets/" . this->sheets[i]["xmlname"] . "\"/>";
            let i = i + 1;
        }

        let xml = xml . "<Relationship Id=\"rId" . strval(this->getSheetsCount() + 2) . "\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings\" Target=\"sharedStrings.xml\"/>\n</Relationships>";
        return (string)xml;
    }
    /**
     * @return string
     */
    protected function buildContentTypesXML() -> string
    {
        var xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">\n<Override PartName=\"/_rels/.rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>\n<Override PartName=\"/xl/_rels/workbook.xml.rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>\n<Override PartName=\"/xl/workbook.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>";
        int i = 0;
        while i < this->getSheetsCount() {
            let xml = xml . "<Override PartName=\"/xl/worksheets/" . this->sheets[i]["xmlname"] . "\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>";
            let i = i + 1;
        }
        let xml = xml . "<Override PartName=\"/xl/sharedStrings.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sharedStrings+xml\"/>\n<Override PartName=\"/xl/styles.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>\n<Override PartName=\"/docProps/core.xml\" ContentType=\"application/vnd.openxmlformats-package.core-properties+xml\"/>\n<Override PartName=\"/docProps/app.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.extended-properties+xml\"/>\n</Types>";
        return (string)xml;
    }
    /**
     * @param array data
     * @param string sheetName
     * @return boolean
     */
    public function addSheet(array data, string sheetName = "Sheet1") -> boolean
    {
        string content  = "";
        let content = (string)this->sheetTemplate;

        int tabSelected = this->getSheetsCount() == 0 ? 1 : 0;
        let content     = str_replace("{$tabSelected}", tabSelected, content);

        int i       = 1;
        int j       = 0;
        array rowStr   = [];
        array cellStr  = [];
        string _rowStr = "";
        string cellLabel = "";
        string _cellStr  = "";
        int maxCellNumber = 0;
        var row;
        var cell;
        for row in data {
            let _rowStr = "<row collapsed=\"false\" customFormat=\"false\" customHeight=\"false\" hidden=\"false\" ht=\"12.1\" outlineLevel=\"0\" r=\"" . strval(i) . "\">";
            let j       = 1;
            let cellStr = [];
            for cell in row {
                let cellLabel = (string)this->getCellMark(i - 1, j - 1);
                let _cellStr  = "<c r=\"" . cellLabel . "\" s=\"0\" t=\"inlineStr\"><is><t>" . this->xmlSpecialChars(cell) . "</t></is></c>";
                let cellStr[] = _cellStr;
                let j = j + 1;
                if j > maxCellNumber {
                    let maxCellNumber = j;
                }
            }
            let _rowStr .= cellStr->join("") . "</row>";
            let rowStr[] = _rowStr;
            let i = i + 1;
        }
        let content    = str_replace("{$rows}", rowStr->join(""), content);
        string maxCell = (string)this->getCellMark(count(data) - 1, maxCellNumber);
        let content    = str_replace("{$maxCell}", maxCell, content);
        array sheet    = ["name": sheetName, "xmlname": "sheet" . strval(this->getSheetsCount() + 1) . ".xml", "content": content];
        let this->sheets[] = sheet;
        this->setSheetsCount(count(this->sheets));
        return true;
    }
    /**
     * Encode string , so it could fit for excel
     * @param val string
     * @return string
     */
    protected function xmlSpecialChars(string val) -> string
    {
        return str_replace("'", "&#39;", htmlspecialchars(val));
    }

    /**
     * convert row number and column number to column label A1-ZZ.
     * @param int rowNumber
     * @param int columnNumber
     * @return string
     */
    protected function getCellMark(int rowNumber, int columnNumber) -> string
    {
        string r = "";
        while columnNumber >= 0 {
            let r = chr(columnNumber % 26 + 0x41) . r;
            let columnNumber = intval(columnNumber / 26) - 1;
        }
        return r . strval(rowNumber + 1);
    }

}
