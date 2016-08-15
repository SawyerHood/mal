<?hh
require_once 'types.hh';

function malAdd(MalType ...$args): MalType {
  return array_reduce($args, ($a, $b) ==> {
    return new IntegerType($a->getValue() + $b->getValue());
  }, new IntegerType(0));
}

function malSub(MalType ...$args): MalType {
  return array_reduce(array_slice($args, 1), ($a, $b) ==> {
    return new IntegerType($a->getValue() - $b->getValue());
  }, $args[0]);
}

function malDiv(MalType ...$args): MalType {
  return array_reduce(array_slice($args, 1), ($a, $b) ==> {
    return new IntegerType((int) ($a->getValue() / $b->getValue()));
  }, $args[0]);
}

function malMult(MalType ...$args): MalType {
  return array_reduce($args, ($a, $b) ==> {
    return new IntegerType($a->getValue() * $b->getValue());
  }, 1);
}

class Enviornment {
  private function __construct(private Map<string, callable> $envMap) {
  }

  public static function defaultEnviornment(): Enviornment {
    return new Enviornment(self::getDefaultEnvMap());
  }

  public static function getDefaultEnvMap(): Map {
    return Map {
      '+' => fun('malAdd'),
      '-' => fun('malSub'),
      '*' => fun('malMult'),
      '/' => fun('malDiv'),
    };
  }

  public function evaluate(MalType $ast): MalType {
    if ($ast instanceof SymbolType) {
      if (!$this->envMap->containsKey($ast->getValue())) {
        throw new Exception("Symbol not found.", 1);
      }
      return $ast;
    } else if ($ast instanceof ListType) {
      $listValues = $ast->getValue()->map(($node)==> {
        return $this->evaluate($node);
      });
      return call_user_func_array($this->envMap[(string) $listValues[0]->getValue()], $listValues->slice(1, count($listValues)));
    } else {
      return $ast;
    }
  }
}
