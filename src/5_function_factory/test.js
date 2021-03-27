(function() {
  const addon = require("./binding.js");
  const fn = addon.createFunction();
  console.log(fn());
})();