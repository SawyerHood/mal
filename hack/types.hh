<?hh

function vecToString(Vector<MalType> $values) {
  return $values->map(($value) ==> {
    return (string) $value;
  });
}

function prettyPrintVecType(Vector<MalType> $values, string $leftWrapper, string $rightWrapper): string {
  return $leftWrapper . implode(' ', vecToString($values)) . $rightWrapper;
}

abstract class MalType {
  public abstract function getValue(): mixed;

  public function __toString(): string {
    return (string) $this->getValue();
  }
}

class IntegerType extends MalType {
  public function __construct(private int $value) {}

  public function getValue(): int {
    return $this->value;
  }
}

class ListType extends MalType {
  public function __construct(private Vector<MalType> $values) {}

  public function getValue(): Vector<MalType> {
    return $this->values;
  }

  public function __toString(): string {
    return prettyPrintVecType($this->values, '(', ')');
  }
}

class MapType extends MalType {
  public function __construct(private Vector<MalType> $values) {}

  public function getValue(): Vector<MalType> {
    return $this->values;
  }

  public function __toString(): string {
    return prettyPrintVecType($this->values, '{', '}');
  }
}

class VectorType extends MalType {
  public function __construct(private Vector<MalType> $values) {}

  public function getValue(): Vector<MalType> {
    return $this->values;
  }

  public function __toString(): string {
    return prettyPrintVecType($this->values, '[', ']');
  }
}

class SymbolType extends MalType {
  public function __construct(private string $value) {}

  public function getValue(): string {
    return $this->value;
  }
}
