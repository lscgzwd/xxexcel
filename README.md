XxExcel
---------
a fast and simple excel2007 parser and writer php extension. which is develop by zephir language.

Requirements
------------

To compile xxexcel:

* [re2c](http://re2c.org/)
* [zephir](https://github.com/phalcon/zephir)

To build the PHP extension:

* g++ >= 4.4/clang++ >= 3.x/vc++ 9
* gnu make 3.81 or later
* php development headers and tools
* you must can exec php,phpize,php-config in your console without any path(and your php/bin to you path or link these commands to usr/bin)

Installation
------------

* Install zephir first. [see](https://github.com/phalcon/zephir)
* Fork and clone this project
* exec zephir build
* add extension=xxexcel.so to to php.ini

Usage
------------

`

        $t     = strval(microtime(true));
        $excel = new \XxExcel\Reader();
        $excel->setMaxRow(5002);
        $excel->open('/home/nginx/1.xlsx');
        $data2 = $excel->getSheetDataByIndex(1);
        echo sprintf('%.2f', memory_get_usage() / 1024 / 1024);
        echo PHP_EOL;
        echo bcsub(strval(microtime(true)), $t, 4);
        echo PHP_EOL;


        $w = new \XxExcel\Writer();
        $w->addSheet($data2);
        $w->build('/home/nginx/test.xlsx');

`
