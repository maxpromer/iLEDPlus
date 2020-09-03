Blockly.Blocks['ledplus'] = {
  init: function() {
    this.appendValueInput("number")
        .setCheck("Number")
        .appendField("LED 16x8 show number");
    this.appendDummyInput()
        .appendField("base")
        .appendField(new Blockly.FieldDropdown([["DEC","10"], ["BIN","2"], ["OCT","8"], ["HEX","16"]]), "base");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(165);
    this.setTooltip("Show number in LED 16x8");
    this.setHelpUrl("");
  },
	xmlToolbox: function() {
		return `
		<block type="ledplus">
			<value name="number">
				<shadow type="math_number">
					<field name="VALUE">0</field>
				</shadow>
			</value>
		</block>
		`;
	}
};
