const person = {
  name: ['John', 'Smith'],
  age: 42,
  
  greeting: function() {
    return `Hello, ${this.name.join(' ')}!`;
  }
};

console.log(person.name);
console.log(person.age);
console.log(person.greeting());
console.log(person['age']);
