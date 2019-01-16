function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33179, y = 32880, z = 11})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33179, y = 32880, z = 11}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33179, y = 32880, z = 11})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33179, y = 32880, z = 11}, 11)
end
