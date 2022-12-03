import {readFileSync} from 'fs';

const input = readFileSync(`input.txt`).toString('utf8')

const elves = [0]

input.split(`\n`).forEach(e => {
    if (e == "") {
        elves.push(0);
        return;
    }
    
    elves[elves.length-1] += Number.parseInt(e) || 0;
});

const max = elves.sort((a, b) => b - a);

console.log(max[0] + max[1] + max[2]);
