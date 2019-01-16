function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33149, y = 32870, z = 11})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33149, y = 32870, z = 11}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33149, y = 32870, z = 11})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33149, y = 32870, z = 11}, 11)
end
