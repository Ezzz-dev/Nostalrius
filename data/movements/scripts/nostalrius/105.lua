function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33190, y = 32947, z = 15})
	Game.sendMagicEffect({x = 33183, y = 32757, z = 15}, 11)
	Game.sendMagicEffect({x = 33191, y = 32947, z = 15}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33190, y = 32947, z = 15})
	Game.sendMagicEffect({x = 33183, y = 32757, z = 15}, 11)
	Game.sendMagicEffect({x = 33191, y = 32947, z = 15}, 11)
end
