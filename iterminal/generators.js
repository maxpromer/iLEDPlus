Blockly.JavaScript['ledplus'] = function(block) {
  var value_number = Blockly.JavaScript.valueToCode(block, 'number', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_base = block.getFieldValue('base');
  var code = `ht16k33.show(DEV_IO.iTerminal().numberToBuffer(${value_number}, ${dropdown_base}, 0));\n`;
  return code;
};

Blockly.JavaScript['ledplus_show_time'] = function(block) {
  var value_n1 = Blockly.JavaScript.valueToCode(block, 'n1', Blockly.JavaScript.ORDER_ATOMIC);
  var value_n2 = Blockly.JavaScript.valueToCode(block, 'n2', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_colon = block.getFieldValue('colon');
  var code = `ht16k33.show(DEV_IO.iTerminal().timeToBuffer(${value_n1}, ${value_n2}, ${dropdown_colon}));\n`;
  return code;
};
