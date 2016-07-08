namespace XxExcel;

/**
 * Class Reader excel2007 解析类
 * @package XxExcel
 */
class Reader
{
    /**
     * @var \ZipArchive
     */
    protected zip;
    protected currentSheet   = 1 {
        set, get
    };
    protected sheetInfos     = [] {
        set, get
    };
    protected sharedStrings  = [] {
        set, get
    };
    protected sheetDatas     = [] {
        set, get
    };
    protected maxRow         = 5000 {
        set, get
    };
    /**
     * read an excel2007 file
     * @param string filename
     * @param string type
     * @return boolean
     */
    public function open(string filename, string type = "Excel2007") -> boolean
    {
        var _zip;
        let _zip = new \ZipArchive();
        _zip->open(filename);
        let this->zip = _zip;
        this->readSharedString();
        return true;
    }
    protected function readSharedString()
    {
        var xml;
        let xml = new \XMLReader();
        var _xmlString;
        let _xmlString = this->zip->getFromName("xl/sharedStrings.xml");
        xml->xml(_xmlString);
        while xml->read() {
            if xml->name == "t" && xml->nodeType == \XMLReader::ELEMENT {
                let this->sharedStrings[] = xml->readString();
            }
        }
    }
    public function getSheetDataByIndex(index)
    {
        this->setCurrentSheet(index);
        if isset(this->sheetDatas[this->currentSheet]) {
            return this->sheetDatas[this->currentSheet];
        }
        string sheetFile;
        let sheetFile = "xl/worksheets/sheet" . this->currentSheet . ".xml";
        var xml;
        let xml = new \XMLReader();
        xml->xml(this->zip->getFromName(sheetFile));
        array rows = [];
        array sharedStrings = (array)this->getSharedStrings();
        int j    = 0;
        var t;
        var value = "";
        var cr;
        array _rowIndexCache = [];
        var _rowIndex = 0;
        var maxRow = this->getMaxRow();
        string nodeName = "c";
        string attrNameR = "r";
        string attrNameT = "t";
        string regx = "/\\D*/";
        string blank = "";
        while xml->read() {
            if xml->name == nodeName && xml->nodeType == \XMLReader::ELEMENT {
                let cr = xml->getAttribute(attrNameR);
                let t = xml->getAttribute(attrNameT);
                if isset(_rowIndexCache[cr]) {
                    let _rowIndex = _rowIndexCache[cr];
                } else {
                    let _rowIndex = preg_replace(regx, blank, cr);
                    let _rowIndexCache[cr] = _rowIndex;
                }
                if _rowIndex > maxRow {
                    continue;
                }
                if empty(t) {
                    let t = "s";
                }
                let value = xml->readString();//strip_tags(xml->readInnerXML());
                if t == "s" {
                    let value = sharedStrings[value];
                }

                let rows[_rowIndex][cr] = value;
                let j = j + 1;
            }
        }
        let this->sheetDatas[this->currentSheet] = rows;
        return rows;
    }
    /**
     * @param int    rowIndex
     * @param string cell
     * @return mixed
     */
    public function getCellValueByRowAndColumn(int rowIndex = 1, string cell = "A")
    {
        return this->sheetDatas[this->currentSheet][rowIndex - 1][cell . rowIndex];
    }
}
