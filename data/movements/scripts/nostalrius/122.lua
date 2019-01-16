function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33193, y = 32664, z = 15})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33193, y = 32664, z = 15}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33193, y = 32664, z = 15})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33193, y = 32664, z = 15}, 11)
end
