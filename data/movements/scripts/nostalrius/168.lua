function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33279, y = 31592, z = 12})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33279, y = 31592, z = 12}, 15)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33279, y = 31592, z = 12})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33279, y = 31592, z = 12}, 15)
end