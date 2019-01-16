function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32492, y = 31697, z = 07})
	Game.sendMagicEffect({x = 32492, y = 31697, z = 07}, 13)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32492, y = 31697, z = 07})
	Game.sendMagicEffect({x = 32492, y = 31697, z = 07}, 13)
end
