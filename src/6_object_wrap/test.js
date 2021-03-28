(function () {
  const addon = require("./binding.js");
  const Vector = addon.Vector;
  console.log(Vector);

  let vector = new Vector(1, 2);
  console.log(vector);
  console.log("x", vector.x);
  console.log("getX", vector.getX());

  let vector1 = Vector(1, 2);
  console.log("y", vector1.y);
  console.log("getY", vector1.getY());
})();