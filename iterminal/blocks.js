Blockly.Blocks['ledplus'] = {
  init: function() {
    this.jsonInit({
      "type": "ledplus",
      "message0": Blockly.Msg.iLEDPlus_MESSAGE,
      "args0": [
        {
          "type": "input_value",
          "name": "number",
          "check": "Number"
        },
        {
          "type": "field_dropdown",
          "name": "base",
          "options": [
            [
              "10",
              "10"
            ],
            [
              "2",
              "2"
            ],
            [
              "8",
              "8"
            ],
            [
              "16",
              "16"
            ]
          ]
        }
      ],
      "inputsInline": true,
      "previousStatement": null,
      "nextStatement": null,
      "colour": 165,
      "tooltip": Blockly.Msg.iLEDPlus_TOOLTIP,
      "helpUrl": ""
    });
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

Blockly.Blocks['ledplus_show_time'] = {
  init: function() {
    this.jsonInit({
      "type": "ledplus_show_time",
      "message0": Blockly.Msg.iLEDPlus_SHOW_TIME_MESSAGE,
      "args0": [
        {
          "type": "input_value",
          "name": "n1",
          "check": "Number"
        },
        {
          "type": "input_value",
          "name": "n2",
          "check": "Number"
        },
        {
          "type": "field_dropdown",
          "name": "colon",
          "options": [
            [
              Blockly.Msg.iLEDPlus_SHOW_TIME_SHOW_MESSAGE,
              "true"
            ],
            [
              Blockly.Msg.iLEDPlus_SHOW_TIME_HIDE_MESSAGE,
              "false"
            ]
          ]
        }
      ],
      "inputsInline": true,
      "previousStatement": null,
      "nextStatement": null,
      "colour": 165,
      "tooltip": Blockly.Msg.iLEDPlus_SHOW_TIME_TOOLTIP,
      "helpUrl": ""
    });
	},
	xmlToolbox: function() {
		return `
		<block type="ledplus_show_time">
			<value name="n1">
				<shadow type="math_number">
					<field name="VALUE">0</field>
				</shadow>
      </value>
      <value name="n2">
				<shadow type="math_number">
					<field name="VALUE">0</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ledplus_show_lr'] = {
  init: function() {
    this.jsonInit({
      "type": "ledplus_show_lr",
      "message0": Blockly.Msg.iLEDPlus_SHOW_LR_MESSAGE,
      "args0": [
        {
          "type": "input_value",
          "name": "n1",
          "check": "Number"
        },
        {
          "type": "input_value",
          "name": "n2",
          "check": "Number"
        }
      ],
      "inputsInline": true,
      "previousStatement": null,
      "nextStatement": null,
      "colour": 165,
      "tooltip": Blockly.Msg.iLEDPlus_SHOW_LR_TOOLTIP,
      "helpUrl": ""
    });
	},
	xmlToolbox: function() {
		return `
		<block type="ledplus_show_lr">
		</block>
		`;
	}
};

