final class Scanner {
    private let source: String
    private var tokens: [Token] = []
    private var start = 0
    private var current = 0
    private var line = 1

    init(source: String) {
        self.source = source
    }

    func scanTokens() -> [Token] {
        while(!isAtEnd) {
            start = current
            scanToken()
        }

        tokens.append(Token(type: .eof, lexeme: "", literal: nil, line: line))
        return tokens
    }

    private var isAtEnd: Bool { current >= source.count }

    private func scanToken() {
        let c = advance()
        switch c {
        case "(": addToken(type: .leftParen)
        case ")": addToken(type: .rightParen)
        case "{": addToken(type: .leftBrace)
        case "}": addToken(type: .rightBrace)
        case ",": addToken(type: .comma)
        case ".": addToken(type: .dot)
        case "-": addToken(type: .minus)
        case "+": addToken(type: .plus)
        case ";": addToken(type: .semicolon)
        case "*": addToken(type: .star)

        case "!": addToken(type: match("=") ? .bangEqual : .bang)
        case "=": addToken(type: match("=") ? .equalEqual : .equal)
        case "<": addToken(type: match("=") ? .lessEqual : .less)
        case ">": addToken(type: match("=") ? .greaterEqual : .greater)

        default: error(line: line, message: "Unexpected character.")
        }

    }

    private func advance() -> Character {
        let index = source.index(source.startIndex, offsetBy: current)
        current += 1
        return source[index]
    }

    private func match(_ expected: Character) -> Bool {
        guard !isAtEnd else { return false }

        if source.character(at: current) == expected {
            current += 1
            return true
        } else {
            return false
        }
    }

    private func addToken(type: TokenType, literal: Any? = nil) {
        tokens.append(
            Token(
                type: type,
                lexeme: source.substring(at: start..<current),
                literal: literal,
                line: line
            )
        )
    }
}

extension String {
    func index(at offset: Int) -> String.Index {
        index(startIndex, offsetBy: offset)
    }

    func character(at offset: Int) -> Character {
        self[index(at: offset)]
    }

    func substring(at range: Range<Int>) -> String {
        String(self[index(at: range.lowerBound)..<index(at: range.upperBound)])
    }
}
