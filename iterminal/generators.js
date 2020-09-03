Blockly.JavaScript['ledplus'] = function(block) {
  var value_number = Blockly.JavaScript.valueToCode(block, 'number', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_base = block.getFieldValue('base');
  var code = `ht16k33.show(DEV_IO.iTerminal().numberToBuffer(${value_number}, ${dropdown_base}, 0));\n`;
  return code;
};
