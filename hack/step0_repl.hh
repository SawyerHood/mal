<?hh

function main() {
  do {
    print 'user> ';
    $input = trim(fgets(STDIN));
    if ($input === false)
      break;
    print repMal($input);
  } while (true);
}

function repMal(string $in) {
  return printMal(evalMal(readMal($in)));
}

function readMal(string $in): string {
  return $in;
}

function evalMal(string $in) {
  return $in;
}

function printMal(string $in) {
  return $in;
}

main();
