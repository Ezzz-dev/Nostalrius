function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33211, y = 32700, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33211, y = 32700, z = 13}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33211, y = 32700, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33211, y = 32700, z = 13}, 11)
end
