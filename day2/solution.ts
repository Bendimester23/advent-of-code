import {readFileSync} from 'fs';

function getScoreForMove(move: string) {
    return {
        X: 1,
        Y: 2,
        Z: 3,
    }[move]
}

function getNum(inp: string) {
    return {
        A: 1,
        B: 2,
        C: 3,
        X: 1,
        Y: 2,
        Z: 3,
    }[inp]
}

function getScoreForWinning(me: string, opponent: string) {
    if (getNum(me) == getNum(opponent)) return 3;

    if (
        (getNum(opponent) == 1 && getNum(me) == 3) ||
        (getNum(opponent) == 2 && getNum(me) == 1) ||
        (getNum(opponent) == 3 && getNum(me) == 2)
    ) return 0;

    return 6;
}

function getMoveBasedOnOutcome(opponent: string, outcome: string) {
    if (outcome == 'Y') {
        return {
            A: 'X',
            B: 'Y',
            C: 'Z'
        }[opponent]
    }

    if (outcome == 'X') {
        return {
            A: 'Z',
            B: 'X',
            C: 'Y'
        }[opponent]
    }

    return {
        A: 'Y',
        B: 'Z',
        C: 'X'
    }[opponent]
}

const input = readFileSync(`input.txt`).toString('utf8').split(`\n`).map(e => {
    let other = e.split(` `)[0]
    let me = e.split(` `)[1]
    
    return (getScoreForMove(getMoveBasedOnOutcome(other, me) || "") || 0) + ({X: 0, Y: 3, Z: 6}[me] || 0)
}).reduce((a, b) => a+b)

console.log(input);

