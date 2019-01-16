function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33255, y = 32839, z = 09})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33255, y = 32839, z = 09}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33255, y = 32839, z = 09})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33255, y = 32839, z = 09}, 11)
end
