function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33080, y = 32569, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33080, y = 32569, z = 13}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33080, y = 32569, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33080, y = 32569, z = 13}, 11)
end
