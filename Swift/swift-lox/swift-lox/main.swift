import Foundation

import Foundation

var hadError = false

let args = CommandLine.arguments // arg[0] is always present and is the name of the executable

switch args.count {
case 1:
    runPrompt()
case 2:
    do {
        let contents = try String(contentsOfFile: args[1], encoding: .utf8)
        run(source: contents)
        if hadError { exit(65) }
    } catch {
        print("Error: \(error)")
    }
default:
    print("Usage: jlox [script]")
    exit(64)
}

func run(source: String) {
    let scanner = Scanner(source: source)
    let tokens = scanner.scanTokens()
    print("Tokens: \(tokens)")
}

func runPrompt() {
    while true {
        print("> ", terminator: "")
        guard let line = readLine() else { break }
        run(source: line)
        hadError = false
    }
}

func error(line: Int, message: String) {
    report(line: line, position: "", message: message)
}

func report(line: Int, position: String, message: String) {
    fputs("[line \(line)] Error\(position): \(message)\n", stderr)
    hadError = true
}

