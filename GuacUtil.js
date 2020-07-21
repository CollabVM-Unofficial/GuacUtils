// Credit: https://github.com/CollabVM-Unofficial/yanderebot
function decodeCommand(cypher) {
  var sections = [];
  var bump = 0;
  while (sections.length <= 50 && cypher.length >= bump) {
    var current = cypher.substring(bump);
    var length = parseInt(current.substring(current.search(/\./) - 2));
    var paramater = current.substring(
      length.toString().length + 1,
      Math.floor(length / 10) + 2 + length
    );
    sections[sections.length] = paramater;
    bump += Math.floor(length / 10) + 3 + length;
  }
  sections[sections.length - 1] = sections[sections.length - 1].substring(
    0,
    sections[sections.length - 1].length - 1
  );
  return sections;
}

function encodeCommand(cypher) {
  var command = "";
  for (var i = 0; i < cypher.length; i++) {
    var current = cypher[i];
    command += current.length + "." + current;
    command += i < cypher.length - 1 ? "," : ";";
  }
  return command;
}
