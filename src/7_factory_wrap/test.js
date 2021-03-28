(function () {
  const addon = require("./binding.js");
  const MyObjectFactory = addon.MyObjectFactory;

  let obj1 = MyObjectFactory(0);
  console.log(obj1.add(10));
  console.log(obj1.add(10));
})();