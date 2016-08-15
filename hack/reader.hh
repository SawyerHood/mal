<?hh
require_once 'types.hh';
class Reader {
  const string TOKEN_REGEX = "/[\s,]*(~@|[\[\]{}()'`~^@]|\"(?:\\.|[^\\\"])*\"|;.*|[^\s\[\]{}('\"`,;)]*)/";
  private int $tokenIndex = 0;

  public static function ReaderFactory(string $source): Reader {
    $regOut = [];
    preg_match_all(self::TOKEN_REGEX, $source, $regOut);
    list($tokensArr) = $regOut;
    array_pop($tokensArr);
    $tokens = new Vector($tokensArr);
    return new Reader($tokens);
  }

  private function __construct(private Vector<string> $tokens) {}

  public function read(): MalType {
    return $this->readForm();
  }

  public function next(): void {
      $this->tokenIndex++;
  }

  public function peek(): string {
    return trim($this->tokens[$this->tokenIndex], " \t\n\r\0\x0B,");
  }

  private function readForm(): MalType {
    $token = $this->peek();
    $toReturn = null;
    switch ($token) {
      case '(':
        $this->next();
        $toReturn = $this->readList();
        break;
      default:
        $toReturn = $this->readAtom();
        break;
    }
    $this->next();
    return $toReturn;
  }

  private function readList(): MalType {
    $list = Vector {};
    while(!$this->isDone() && $this->peek() !== ')') {
      $list[] = $this->readForm();
    }
    return new ListType($list);
  }

  private function isDone(): bool {
    return $this->tokenIndex >= $this->tokens->count();
  }

  private function readAtom(): MalType {
    $token = $this->peek();
    // This could be dangerous, we are using this as a catch all until I add other number types
    if (is_numeric($token)) {
      return new IntegerType((int) $token);
    } else {
      return new SymbolType($token);
    }
  }

}
