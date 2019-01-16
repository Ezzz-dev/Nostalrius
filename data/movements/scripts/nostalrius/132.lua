function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33133, y = 32642, z = 08})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33133, y = 32642, z = 08}, 15)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33133, y = 32642, z = 08})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33133, y = 32642, z = 08}, 15)
end
