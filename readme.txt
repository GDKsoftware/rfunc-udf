====================================================================
      Файл readme.txt

      Библиотека функций rFunc для СУБД InterBase.
      Описание.

      Copyright 1998-2003 Polaris Software
      http://rfunc.sourceforge.net
      mailto:rFunc@mail.ru

====================================================================

Для более удобного просмотра этого файла разверните окно 
Вашей программы просмотра на весь экран и включите режим 
Перенос по словам (Word wrap).

СОДЕРЖАНИЕ

1. Краткое описание
2. Порядок компиляции
3. Порядок установки
4. Порядок распространения
5. Состав файлов
6. Благодарности

----------------------------------------------

1. Краткое описание
-------------------

Библиотека функций rFunc (далее - библиотека) предназначена для расширения возможностей СУБД InterBase. Включает в себе более 140 строковых, числовых, битовых функций, работы с датами, BLOBами, пользователями и др. функций.
Также библиотека содержит парсер (вычислитель выражений), который позволяет выполнять числовые выражения, заданные в виде строки, с передачей параметров. Через него можно вычислять и тригонометрические функции. 

Список функций:
  > Числовые: Abs Ceil Floor MaxNum MinNum Power Round SoftRound Z IIf DIf DZero Div Mod InitRandom GetRandom
  > Парсер: CalcExpr ExprIsValid
  > Строковые: Chr Ord StrReplace StrStuff LTrim RTrim StrLen StrPos StrRepeat SubStr Trim CIf StrCount WordCount WordNum RLower RUpper PadLeft PadRight RLatin RTranslit
  > Даты: DateToStr DayPerMonth Dow EncodeDate EncodeDateTime ExtractDate ExtractDay ExtractMonth ExtractYear ExtractHour ExtractMinute ExtractSecond ExtractWeekDay ExtractYearDay Quarter FirstDayMonth LastDayMonth IsLeapYear DaysBetween DtIf IncDate IncDateTime
  > BLOB: B_Line B_Line_Count B_Max_Segment B_Number_Segments B_Put_Segment B_SubStr B_Total_Length
  > Битовые: BitAnd BitNot BitOr BitXor GetBit SetBit
  > Пользователи: Add_User Modify_User Delete_User (только для IB 5.x и выше)
  > Прочее: MsgBox (только Windows)
Возвращаемые строки в строковых функциях имеют максимальную длину 255 символов. Для возврата длинных строк используйте функции с префиксом Long (длина до 16K).
Полное описание функций приведено в каталоге doc.

Библиотека написана на C++, поставляется с полностью открытым исходным кодом (каталог source). Это позволяет скомпилировать ее на любой платформе, поддерживаемой самим Interbase.

В каталоге sql поставляется набор скриптов для добавления, удаления и тестирования функций в Вашей базе данных. Скрипты для удаления и тестирования функций библиотеки не разделены для разных версий IB, поэтому допускаются ошибки при их выполнении.

Поддерживаемые ОС:
  Windows 9x, NT, Me, W2K, XP
  Linux kernel 2.2 и выше
  FreeBSD 5.x
Поддерживаемые версии InterBase:
  для Windows: InterBase 4.2, 5.x, 6.x, Firebird 1.x, Yaffil 1.x.
    для Linux: InterBase      5.x, 6.x, Firebird 1.x.
  для FreeBSD: Firebird 1.x.

Замечание. Далее по тексту IB6 будет означать InterBase 6.x и выше, Firebird 1.x или Yaffil 1.x.

2. Порядок компиляции
---------------------

Для удобства компиляции в архив включены make-файлы с именами makefileN.win и makefileN.linux для Windows и Linux соответственно, где N - версия IB.

Для Windows:

1. Установить один из компиляторов Borland C++.
2. Развернуть архив с библиотекой в какую-нибудь папку.
3. Открыть папку source.
4. Отредактировать make-файл makefile.bc: прописать путь к IB (ключ IBASE), к С++ (BCDIR), к системной папке Windows (SYSDIR).
5. Собрать библиотеку командой
     <папка BC++>\bin\make -f makefile.bc all

Компиляция тестировалась на Free Borland C++ Compiler 5.5 и Borland С++Builder 4.0.

Для Linux:

1. Развернуть архив с библиотекой с помощью mc или командами
     gzip -d rfunc.tar.gz
     tar xvf rfunc.tar
2. Войти в каталог source.
3. Отредактировать make-файл makefile.linux: прописать путь к IB (ключ IBASE).
4. Собрать библиотеку командой
     make -f makefile.linux all

Компиляция тестировалась на RH 6.2 kernel 2.2.14, Mandrake 8.0 kernel 2.4.4.

Для FreeBSD:

1. Развернуть архив с библиотекой с помощью mc или командами
     gzip -d rfunc.tar.gz
     tar xvf rfunc.tar
2. Войти в каталог source.
3. Отредактировать make-файл makefile.freebsd: прописать путь к IB (ключ IBASE).
4. Собрать библиотеку командой
     make -f makefile.freebsd all

Компиляция тестировалась на FreeBSD 5.1.


3. Порядок установки
--------------------

С дистрибутивом поставляется скомпилированная библиотека rFunc только для Firebird 1.x. Для других версий IB необходимо самостоятельно скомпилировать ее или, став зарегистрированным пользователем, получить ее от нас.

Для Windows:

1. Файл RFUNC.DLL необходимо переписать в папку
   вариант 1: <Путь IB>\Bin (для IB6 - <Путь IB>\UDF), где <Путь IB> - путь к папке, в которой установлен Interbase (рекомендуется).
   вариант 2: Windows\System (для Windows 9x) или WinNT\System32 (Windows NT, 2k).
2. только для IB 5.x: скопировать файл ib_util.dll из <Путь IB>\Lib в <Путь IB>\Bin.

Если на одном компьютере установлено несколько версий серверов Interbase, необходимо использовать библиотеку rFunc, соответствующую установленному клиенту IB (GDS32.DLL).
Рекомендуется перед запуском сервера Interbase заменять GDS32.DLL на соответствующую версии сервера.

Для Linux:

IB 5.x
вариант 1: Скопируйте файл rfunc в каталог /usr/lib.
вариант 2: Скопируйте файл rfunc в какой-нибудь каталог, например, /home/rFunc. Затем для создания ссылки на библиотеку выполните команду ln -s /home/rFunc/rfunc /usr/lib/rfunc. Естественно, что пользователь должен иметь право на создание ссылок в каталоге /usr/lib.

IB6
Скопируйте файл rfunc в каталог <Каталог IB>\UDF.


4. Порядок распространения
--------------------------

Все вопросы, связанные с использованием и распространением библиотеки, регулируются GNU Lesser General Public License.
Текст лицензии находится в файле license.txt.

Библиотека является свободно распространяемым продуктом (freeware) и ее техническая поддержка нами не гарантируется.
Существует возможность НЕОБЯЗАТЕЛЬНОЙ платной (10$) регистрации. Это для тех, кто хочет получать техническую поддержку, иметь право на первоочередное рассмотрение Ваших проблем и включение в библиотеку требуемых функций.
Зарегистрироваться можно по адресу http://www.shareg.com/req.php3?prodid=691&referer=2866.


5. Состав файлов
----------------

Каталоги/Файлы           Описание
------------------------------------------------------------
bin/                     скомпилированная библиотека
rfunc.dll                для Firebird 1.x (Windows)
rfunc                    для Firebird 1.x (Linux)

doc/                     описание
*.html                   страница описания функций (с нашего сайта)
*eng.html                страница описания функций (с нашего англоязычного сайта)
*.gif, polesoft.css      картинки и таблица стилей для html
rfunc.txt                описание функций (win1251)
rfunceng.txt             описание функций (english)
rfunc.koi8               описание функций (koi8r)

source/                  все, что нужно для компиляции
makefile*.*              make-файлы для компиляции для различных версий IB и для Windows и Linux
rblob.*                  функции работы с BLOB
rcalc.*                  парсер
rdatetime.*              функции работы с датами
rfunc.h                  header-файл для rfunc
rfunc*.rc                ресурсный файл c VersionInfo для различных версий IB (только Windows)
rmath.*                  математические функции
rmisc.*                  разные функции
rsecurity.*              функции работы с пользователями
rstring.*                строковые функции
win1251.h                массивы символов для функций rUpper, rLower, rLatin, rTranslit

sql/                     скрипты
rdrop.sql                удаление функций из базы данных
rfunc*.sql               добавление функций в базу данных для различных версий IB
rtest.sql                тестирование функций

changes.txt              история изменений (win1251)
changeseng.txt           история изменений (english)
changes.koi8             история изменений (koi8r)
license.txt              лицензия (english)
readme.txt               файл описания (win1251)
readmeeng.txt            файл описания (english)
readme.koi8              файл описания (koi8r)


6. Благодарности
----------------

Хазацкий Александр
Software developer
Storm International CS B.V.

----------------------------------------------

24.07.2001

С уважением,
Polaris Software, Россия, Краснодар

Спасибо за интерес к нашим продуктам.