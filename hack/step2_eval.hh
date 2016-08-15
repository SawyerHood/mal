<?hh
namespace step2;

require_once 'reader.hh';
require_once 'types.hh';
require_once 'enviornment.hh';
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
  $env = \Enviornment::defaultEnviornment();
  return $env->evaluate($in);
}

function printMal(\MalType $in): string {
  return (string) $in;
}

main();
