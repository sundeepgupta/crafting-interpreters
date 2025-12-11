final class Scanner {
    private let source: String
    private var tokens: [Token] = []
    private var start = 0
    private var current = 0
    private var line = 1

    init(source: String) {
        self.source = source
    }

    private var isAtEnd: Bool { current >= source.count }

    func scanTokens() -> [Token] {
        while(!isAtEnd) {
            start = current
            scanToken()
        }

        tokens.append(Token(type: .eof, lexeme: "", literal: nil, line: line))
        return tokens
    }

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
        let startIndex = source.index(offset: start)
        let endIndex = source.index(offset: current)
        let substring = source[startIndex..<endIndex]

        tokens.append(
            Token(
                type: type,
                lexeme: String(substring),
                literal: literal,
                line: line
            )
        )
    }
}

extension String {
    func index(offset: Int) -> String.Index {
        index(startIndex, offsetBy: offset)
    }

    func character(at index: Int) -> Character {
        self[self.index(offset: index)]
    }
}
