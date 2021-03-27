let addon;

try {
  addon = require("./build/Release/example.node");
} catch (error) {
  addon = require("./build/Debug/example.node");
}

module.exports = addon;