(function () {
  const addon = require("./binding.js");

  const obj1 = addon.createObject(1);
  const obj2 = addon.createObject(2);
  console.log(obj1, obj2, addon.add(obj1, obj2));
})();