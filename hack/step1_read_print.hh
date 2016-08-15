<?hh
namespace step1;

require_once 'reader.hh';
require_once 'types.hh';

function main() {
  do {
    print 'user> ';
    $input = trim(fgets(STDIN));
    if ($input === false)
      break;
    print repMal($input) . "\n";
  } while (true);
}

function repMal(string $in): string {
  return printMal(evalMal(readMal($in)));
}

function readMal(string $in): \MalType {
  $reader = \Reader::ReaderFactory($in);
  return $reader->read();
}

function evalMal(\MalType $in): \MalType {
  return $in;
}

function printMal(\MalType $in): string {
  return (string) $in;
}

main();
