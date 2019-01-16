function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33133, y = 32642, z = 08})
	Game.sendMagicEffect({x = 33124, y = 32759, z = 14}, 11)
	Game.sendMagicEffect({x = 33133, y = 32642, z = 08}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33133, y = 32642, z = 08})
	Game.sendMagicEffect({x = 33124, y = 32759, z = 14}, 11)
	Game.sendMagicEffect({x = 33133, y = 32642, z = 08}, 11)
end
