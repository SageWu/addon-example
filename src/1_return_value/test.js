(function returnValue() {
  const addon = require("./binding.js");
  console.log(addon.getString()); // "hello world"
})();